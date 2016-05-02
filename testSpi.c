#include <bcm2835.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (!bcm2835_init()) {
		printf("oops, could not init bcm2835\n");
		return 1;
	} else {
		printf("Initialized");
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_1024);    // ~ 4 MHz
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

	uint8_t mosi[12] = { 0x60, 0x00 };
	uint8_t miso[12] = { 0 };

	printf("Starting");
	int data[30000];
	for (int i = 0; i < 30000; i++) {
		bcm2835_spi_transfernb(mosi, miso, 2);
//		printf("%d\n", miso[1] + ((miso[0] & 3) << 8));
//		data[i] = miso[1] + ((miso[0] & 3) << 10);
		data[i] = miso[1] + miso[0];
	}

	bcm2835_spi_end();
	bcm2835_close();

	FILE *fp=fopen("output2.csv","wr");

        for(int i=0;i<30000;i++) {
 	      fprintf(fp,"%d,\n",data[i]);
     	}

 

     fclose(fp);
	return 0;
}
