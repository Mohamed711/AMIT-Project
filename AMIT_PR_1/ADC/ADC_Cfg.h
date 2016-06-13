#ifndef ADC_CFG_H_
#define ADC_CFG_H_


/* Register Addresses*/
#define ADCSRA_REG (u8 volatile *const)0x26
#define ADMUX_REG  (u8 volatile *const)0x27
#define SFIOR_REG  (u8 volatile *const)0x50
#define ADCH_REG   (u8 volatile *const)0x25
#define ADCL_REG   (u8 volatile *const)0x24


/* Local Symbols*/
/*Reference Selection Source*/
#define REF_AREF 0x00
#define REF_AVCC 0x40
#define REF_INT  0xC0

/*Prec*/
#define PREC_8  0x20
#define PREC_10 0x00
#define PREC PREC_10

/*Triggering Mode*/
#define TRIG_SINGLE 0x00
#define TRIG_AUTO 0x20
#define TRIG TRIG_SINGLE

/*Devision FACTOR*/
#define DEV_2 0x00
#define DEV_4 0x02
#define DEV_8 0x03
#define DEV_16 0x04
#define DEV_32 0x05
#define DEV_64 0x06
#define DEV_128 0x07
#define DEV_FACTOR DEV_2


/*ADC_Enable*/
#define ADC_Enable 0x80

#define ADC_Disable 0x7f

#define ADC_START_CONV 0x40

#define  ADC_INT_FLAG_MASK 0x10

#endif /* ADC_CFG_H_ */