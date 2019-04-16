
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

#define CLKKEY 0x40004014
#define CCTRL 0x40004018

#define SYST_CSR 0xE000E010
#define SYST_RVR 0xE000E014
#define SYST_CVR 0xE000E018

static void delay ( void )
{
    unsigned int ra;
    for(ra=0;ra<20;ra++)
    {
        while(1)
        {
            if(GET32(SYST_CSR)&0x10000) break;
        }
    }
}

int notmain ( void )
{
    unsigned int ra;

    //GPIO 46
    //GPIO 37
    //GPIO 44
    //GPIO 47

    //CLOCK/2
    //PUT32(CLKKEY,0x47);
    //PUT32(CCTRL,1);
    //PUT32(CLKKEY,0x00);

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

    PUT32(SYST_CSR,4);
    PUT32(SYST_RVR,12000000-1);
    PUT32(SYST_CVR,12000000-1);
    PUT32(SYST_CSR,5);

    while(1)
    {
        PUT32(GPIO_WTSB,1<<(46-32));
        delay();
        PUT32(GPIO_WTCB,1<<(46-32));

        PUT32(GPIO_WTSB,1<<(37-32));
        delay();
        PUT32(GPIO_WTCB,1<<(37-32));

        PUT32(GPIO_WTSB,1<<(44-32));
        delay();
        PUT32(GPIO_WTCB,1<<(44-32));

        PUT32(GPIO_WTSB,1<<(47-32));
        delay();
        PUT32(GPIO_WTCB,1<<(47-32));
    }
    return(0);
}
