
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define PADKEY 0x40010060

#define GPIO_CFGE 0x40010050
#define GPIO_CFGF 0x40010054

#define GPIO_WTSA 0x40010090
#define GPIO_WTSB 0x40010094
#define GPIO_WTCA 0x40010098
#define GPIO_WTCB 0x4001009C

int notmain ( void )
{
    unsigned int ra;

    //GPIO 46
    //GPIO 37
    //GPIO 44
    //GPIO 47

    PUT32(PADKEY,0x73);

    ra=GET32(GPIO_CFGE);
    ra&=(~(0xF<<20)); //pin37
    ra|=     1<<21;
    PUT32(GPIO_CFGE,ra);

    ra=GET32(GPIO_CFGF);
    ra&=(~(0xF<<16)); //pin44
    ra|=     1<<17;
    ra&=(~(0xF<<24)); //pin46
    ra|=     1<<25;
    ra&=(~(0xF<<28)); //pin47
    ra|=     1<<29;
    PUT32(GPIO_CFGF,ra);

    PUT32(PADKEY,0x00);

    while(1)
    {
        PUT32(GPIO_WTSB,1<<(46-32));
        for(ra=0;ra<200000;ra++) dummy(ra);
        PUT32(GPIO_WTCB,1<<(46-32));

        PUT32(GPIO_WTSB,1<<(37-32));
        for(ra=0;ra<200000;ra++) dummy(ra);
        PUT32(GPIO_WTCB,1<<(37-32));

        PUT32(GPIO_WTSB,1<<(44-32));
        for(ra=0;ra<200000;ra++) dummy(ra);
        PUT32(GPIO_WTCB,1<<(44-32));

        PUT32(GPIO_WTSB,1<<(47-32));
        for(ra=0;ra<200000;ra++) dummy(ra);
        PUT32(GPIO_WTCB,1<<(47-32));
    }
    return(0);
}
