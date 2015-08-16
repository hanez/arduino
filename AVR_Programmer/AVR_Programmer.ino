#define PAGESIZE 32     // in (2-byte) words
                        // set to 32 for atmega8
                        // set to 64 for atmega168


#define LED 13

#define RESET 2
#define SCK   3
#define MISO  4
#define MOSI  5

#define CTS   6

typedef unsigned char byte;	// 8 bit
typedef unsigned int  word;	// 16 bit
typedef unsigned long dword;	// 32 bit

dword spibits(int n, byte output);
dword spidword(dword output);
word spiword(word output);
byte spibyte(byte output);
void printhex(byte x);
void printbits(byte x);
void waitforinput(void);
char readchar(void);
byte readnibble(void);
byte readbyte(void);
word readword(void);
void skipline(void);


void setup()
{
	pinMode(RESET, OUTPUT);
	pinMode(SCK,   OUTPUT);
	pinMode(MISO,  INPUT);
	pinMode(MOSI,  OUTPUT);
	pinMode(CTS,   OUTPUT);

	digitalWrite(CTS, HIGH);  // signal NOT clear to send to PC
	Serial.begin(9600);
	Serial.println();
	Serial.println();
	Serial.println("pesco's atmel-programming arduino, (c) 2009");
	Serial.flush();
}


void loop()
{
	byte echo;

	// give RESET a high pulse
	Serial.println();
	Serial.println("reset pulse.");
	digitalWrite(RESET, HIGH);
	delay(50);
	digitalWrite(RESET, LOW);

	// give chip time to init
	delay(50);

	// enter programming mode
	Serial.print("initiate programming: ");
	echo = (spidword(0xAC530000) & 0xFF00) >> 8;

	if(echo == 0x53) {
		byte sig[3];
		byte lock;
		word fuse;

		Serial.println("slave confirms.");

		// read signature byte
		Serial.print("reading signature bytes: 0x");
		sig[0] = spidword(0x30000000) & 0xFF;
		printhex(sig[0]);
		sig[1] = spidword(0x30000100) & 0xFF;
		printhex(sig[1]);
		sig[2] = spidword(0x30000200) & 0xFF;
		printhex(sig[2]);
		Serial.println();

		// read lock bits
		Serial.print("reading lock bits: ");
		lock = spidword(0x58000000) & 0x3F;
		printbits(lock);
		Serial.println();

		// read fuse bits
		Serial.print("reading fuse bits: ");
		fuse = (spidword(0x58080000) & 0xFF) << 8;     // high byte
		printbits(fuse >> 8);
		fuse |= spidword(0x50000000) & 0xFF;           // low byte
		printbits(fuse & 0xFF);
		Serial.println();

		// wait for firmware image on serial
		Serial.print("awaiting hex file...");
		waitforinput();
		Serial.println(" incoming...");
		
		// perform chip erase
		Serial.println("chip erase.");
		spidword(0xAC800000);
		delay(10); // WD_ERASE

		// write anything that comes over serial into program mem
		Serial.print("writing to flash memory: (pagesize ");
		Serial.print(PAGESIZE);
		Serial.println(" words)");
		word addr=0;
		byte hi=0;
		boolean done=false;
		word count=0;
		while(!done) {
			byte n;  // record length
			byte t;  // record type

			// read one line of the hex file
			readchar();      // colon
			n = readbyte();  // record length
			readword();      // address
			t = readbyte();  // type
			if(t == 0) {
				// data record
				Serial.print(' ');
				for(int i=0; i<n; i++) {
					byte b;

					b = readbyte();
					if(b!=0xFF)     // erased mem is filled with ones
					{
						spibyte(0x40 | (hi<<3));
						spiword(addr);
						spibyte(b);
						delay(5);
					}
					printhex(b);

					count++;
					addr += hi;    // increment after loading high byte
					hi = 1-hi;

					// write when we hit the next page
					if(addr%PAGESIZE == 0 && hi==0) {
						spibyte(0x4C);
						spiword(addr-PAGESIZE);
						spibyte(0x00);
						delay(50); // WD_FLASH
					}
				}
				Serial.println();
			} else if(t == 1) {
				// end record
				done = true;
				// write the last page
				spibyte(0x4C);
				spiword(addr);
				spibyte(0x00);
				delay(50); // WD_FLASH
			}
			skipline();
		}
		Serial.println("programming complete.");
		Serial.print(count);
		Serial.println(" bytes written.");

		// let the slave start
		Serial.println("slave start.");
		digitalWrite(MOSI, LOW);    // clear output state
		digitalWrite(RESET, HIGH);
		Serial.println("press any key for another round.");
		Serial.flush();
		readchar();
	} else {
		Serial.print("not in sync, retry in 1s...");
		delay(1000);
	}
}


dword spibits(int n, dword output)
{
	dword input = 0;

	// exchange n bits over SPI
	for(int i=n-1; i>=0; i--)
	{
		digitalWrite(MOSI, (output >> i) & 1);
		//delay(1);
		digitalWrite(SCK, HIGH);
		input |= digitalRead(MISO) << i;
		//delay(1);
		digitalWrite(SCK, LOW);
	}

	return input;
}

dword spidword(dword output)
{
	return spibits(32, output);
}

word spiword(word output)
{
	return spibits(16, (dword)output);
}

byte spibyte(byte output)
{
	return spibits(8, (dword)output);
}

void printhex(byte x)
{
	const char digits[] = "0123456789ABCDEF";

	Serial.print(digits[x>>4]);
	Serial.print(digits[x&0x0F]);
}

void printbits(byte x)
{
	for(int i=7; i>=0; i--)
		Serial.print((char)('0' + ((x>>i) & 1)));
}

void waitforinput(void)
{
	if(! Serial.available()) {
		// cheap-ass flow control
		digitalWrite(CTS, LOW);         // clear to send
		while(! Serial.available())
			;
		digitalWrite(CTS, HIGH);	// not clear to send
	}
}

char readchar(void)
{
	waitforinput();
	return Serial.read();
}

byte readnibble(void)
{
	char c;

	c = readchar();
	if(c>='0' && c<='9')
		return (c-'0');
	else if(c>='A' && c<='F')
		return (c-'A' + 10);
	else if(c>='a' && c<='f')
		return (c-'a' + 10);
	else
		return 0;
}

byte readbyte(void)
{
	byte x,y;
	
	x = readnibble();
	y = readnibble();
	
	return ((x<<4) | y);
}

word readword(void)
{
	word x,y;

	x = readbyte();
	y = readbyte();

	return ((x<<8) | y);
}

void skipline(void)
{
	while(readchar() != '\n');
}
