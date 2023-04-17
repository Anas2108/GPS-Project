#define GET_BIT(reg1,bit) ((reg1>>bit)&1)
#define SET(reg,val) reg |= val
#define SET_BIT(reg,val) reg |= (1<<val)
#define CLR(reg,val) reg &=~val
#define CLR_BIT(reg,val) reg &=~(1<<val)

