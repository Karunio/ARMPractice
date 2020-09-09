#define RCC             0x40023800
#define RCC_AHB1ENR     *((unsigned int *)(RCC + 0x30))

#define GPIOx_MODER     0x00
#define GPIOx_OTYPER    0x04
#define GPIOx_OSPEEDR   0x08
#define GPIOx_PUPDR     0x0C
#define GPIOx_IDR       0x10
#define GPIOx_ODR       0x14

#define GPIOC           0x40020800
#define GPIOCEN         0x00000004
#define GPIOC_MODER     *((unsigned int*)(GPIOC + GPIOx_MODER  ))
#define GPIOC_OTYPER    *((unsigned int*)(GPIOC + GPIOx_OTYPER ))
#define GPIOC_OSPEEDR   *((unsigned int*)(GPIOC + GPIOx_OSPEEDR))
#define GPIOC_PUPDR     *((unsigned int*)(GPIOC + GPIOx_PUPDR  ))
#define GPIOC_IDR       *((unsigned int*)(GPIOC + GPIOx_IDR    ))
#define GPIOC_ODR       *((unsigned int*)(GPIOC + GPIOx_ODR    ))

static void Delay(const unsigned int millis);

int main()
{
  RCC_AHB1ENR = GPIOCEN;
  GPIOC_MODER = 0x00000055;
  GPIOC_OTYPER = 0x00000000;
  GPIOC_OSPEEDR = 0x00000000;
  GPIOC_PUPDR = 0x00000000;
  
  while(1)
  {
    GPIOC_ODR = 0x0005;
    Delay(1000);
    GPIOC_ODR = 0x000A;
    Delay(1000);
  }
}

static void Delay(const unsigned int millis)
{
  for(unsigned int i = 0; i < (5000 * millis); i++);
}