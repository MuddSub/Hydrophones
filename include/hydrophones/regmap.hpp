#ifndef REGMAP
#define REGMAP


volatile uint16_t* const  CLK_CTRL  = (uint16_t*) 0x000;
volatile uint16_t* const  PLL_DEN = (uint16_t*) 0x001;
volatile uint16_t* const  PLL_NUM = (uint16_t*) 0x002;
volatile uint16_t* const  PLL_CTRL = (uint16_t*) 0x003;
volatile uint16_t* const  PLL_LOCK = (uint16_t*) 0x005;
volatile uint16_t* const  MASTER_ENABLE = (uint16_t*) 0x040;
volatile uint16_t* const  ADC_ENABLE = (uint16_t*) 0x041;
volatile uint16_t* const  POWER_ENABLE = (uint16_t*) 0x042;
volatile uint16_t* const  ASIL_CLEAR = (uint16_t*) 0x080;
volatile uint16_t* const  ASIL_MASK = (uint16_t*) 0x081;
volatile uint16_t* const  ASIL_FLAG = (uint16_t*) 0x082;
volatile uint16_t* const  ASIL_ERROR = (uint16_t*) 0x083;
volatile uint16_t* const  CRC_VALUE_L = (uint16_t*) 0x084;
volatile uint16_t* const  CRC_VALUE_L = (uint16_t*) 0x084;
volatile uint16_t* const  CRC_VALUE_H = (uint16_t*) 0x085;
volatile uint16_t* const  RM_CRC_ENABLE = (uint16_t*) 0x086;
volatile uint16_t* const  RM_CRC_DONE = (uint16_t*) 0x087;
volatile uint16_t* const  RM_CRC_VALUE_L = (uint16_t*) 0x088;
volatile uint16_t* const  RM_CRC_VALUE_H = (uint16_t*) 0x089;
volatile uint16_t* const  LNA_GAIN = (uint16_t*) 0x100;
volatile uint16_t* const  PGA_GAIN = (uint16_t*) 0x101;
volatile uint16_t* const  ADC_ROUTING1_4 = (uint16_t*) 0x102;
volatile uint16_t* const  DECIM_RATE = (uint16_t*) 0x140;
volatile uint16_t* const  HIGH_PASS = (uint16_t*) 0x141;
volatile uint16_t* const  ACK_MODE = (uint16_t*) 0x143;
volatile uint16_t* const  TRUNCATE_MODE = (uint16_t*) 0x144;
volatile uint16_t* const  SERIAL_MODE = (uint16_t*) 0x1C0;
volatile uint16_t* const  PARALLEL_MODE = (uint16_t*) 0x1C1;
volatile uint16_t* const  OUTPUT_MODE = (uint16_t*) 0x1C2;
volatile uint16_t* const  ADC_READ_0 = (uint16_t*) 0x200;
volatile uint16_t* const  ADC_READ1 = (uint16_t*) 0x201;
volatile uint16_t* const  ADC_SPEED = (uint16_t*) 0x210;
volatile uint16_t* const  ADC_MODE = (uint16_t*) 0x211;
volatile uint16_t* const  MP0_MODE = (uint16_t*) 0x250;
volatile uint16_t* const  MP1_MODE = (uint16_t*) 0x251;
volatile uint16_t* const  MP0_WRITE = (uint16_t*) 0x260;
volatile uint16_t* const  MP1_WRITE = (uint16_t*) 0x261;
volatile uint16_t* const  MP0_READ = (uint16_t*) 0x270;
volatile uint16_t* const  MP1_READ = (uint16_t*) 0x271;
volatile uint16_t* const  SPI_CLK_PIN = (uint16_t*) 0x280;
volatile uint16_t* const  MISO_PIN = (uint16_t*) 0x281;
volatile uint16_t* const  SS_PIN = (uint16_t*) 0x282;
volatile uint16_t* const  MOSI_PIN = (uint16_t*) 0x283;
volatile uint16_t* const  ADDR15_PIN = (uint16_t*) 0x284;
volatile uint16_t* const  FAULT_PIN = (uint16_t*) 0x285;
volatile uint16_t* const  FS_ADC_PIN = (uint16_t*) 0x286;
volatile uint16_t* const  CS_PIN = (uint16_t*) 0x287;
volatile uint16_t* const  SCLK_ADC_PIN = (uint16_t*) 0x288;
volatile uint16_t* const  ADC_DOUT0_PIN = (uint16_t*) 0x289;
volatile uint16_t* const  ADC_DOUT1_PIN = (uint16_t*) 0x28A;
volatile uint16_t* const  ADC_DOUT2_PIN = (uint16_t*) 0x28B;
volatile uint16_t* const  ADC_DOUT3_PIN = (uint16_t*) 0x28C;
volatile uint16_t* const  ADC_DOUT4_PIN = (uint16_t*) 0x28D;
volatile uint16_t* const  ADC_DOUT5_PIN = (uint16_t*) 0x28E;
volatile uint16_t* const  DATA_READY_PIN = (uint16_t*) 0x291;
volatile uint16_t* const  XTAL_CTRL = (uint16_t*) 0x292;
volatile uint16_t* const  ADC_SETTING1 = (uint16_t*) 0x301;
volatile uint16_t* const  ADC_SETTING2 = (uint16_t*) 0x308;
volatile uint16_t* const  ADC_SETTING3 = (uint16_t*) 0x30A;
volatile uint16_t* const  DEJITTER_WINDOW = (uint16_t*) 0x30E;
volatile uint16_t* const  CRC_EN = (uint16_t*) 0xFD00;


//Pins (all in terms of WiringPI numbers;
#define N_CONV_START_PIN 7    //BCM 4
#define N_FAULT_PIN 27        //BCM 16
#define N_PG_PIN 25           //BCM 26
#define SW1_PIN 23            //BCM 13
#define SW2_PIN 26            //BCM 12
#define N_STATUS_R_PIN 1      //BCM 18
#define N_STATUS_G_PIN 24     //BCM 19
#define N_STATUS_B_PIN 28     //BCM 20
#define N_RESET_PWDN_PIN 6    //BCM 25
#define DATA_READY_PIN 22     //BCM 6
#define SCLK_ADC_PIN 21       //BCM 5

//These are in terms of the broadcom pins, because that's how we read them
#define DIN_PIN_0 24
#define DIN_PIN_1 22
#define DIN_PIN_2 21
#define DIN_PIN_3 27
#define DIN_PIN_4 18
#define DIN_PIN_5 17
#define DIN_PIN_6 15
#define DIN_PIN_7 14


volatile uint32_t* const  RPI_GPILEV0 = (uint32_t*) 0x7E200034;
volatile uint32_t* const  RPI_GLILEV1 = (uint32_t*) 0x7E200038;

#endif
