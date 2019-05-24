#include <stdlib.h>

#ifndef __AVR_ATmega2560__
#include <string.h>
#include <stdio.h>
// function from https://github.com/stm32duino/Arduino_Core_STM32/blob/master/cores/arduino/avr/dtostrf.c
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
  //Commented code is the original version
  /*char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;*/

  // Handle negative numbers
  unsigned int negative = 0;
  if (val < 0.0)
  {
     negative = 1;
     val = -val;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (int i=0; i<prec; ++i)
    rounding /= 10.0;

  val += rounding;

  // Extract the integer part of the number
  unsigned long int_part = (unsigned long)val;
  double remainder = val - (double)int_part;

  if(negative)
    int_part = -int_part;

  // Extract digits from the remainder
  unsigned long dec_part = 0;
  double decade = 1.0;
  for(int i=0; i < prec; i++)
    decade *= 10.0;
  remainder *= decade;
  dec_part = (int)remainder;

  sprintf(sout, "%ld.%ld", int_part, dec_part);

  // Handle minimum field width of the output string
  // width is signed value, negative for left adjustment.
  // Range -128,127
  char fmt[129] = "";
  unsigned int w = width;
  if (width < 0) {
    negative = 1;
    w = -width;
  } else {
    negative = 0;
  }

  if(strlen(sout) < w) {
    memset(fmt, ' ', 128);
    fmt[w-strlen(sout)] = '\0';
	if(negative == 0) {
      char *tmp = strdup(sout);
      strcpy(sout,fmt);
      strcat(sout, tmp);
      free(tmp);
    } else {
      // left adjustment
       strcat(sout, fmt);
    }
  }

  return sout;
}
#endif

//adapted from http://www.ars-informatica.ca/eclectic/ftoa-convert-a-floating-point-number-to-a-character-array-on-the-arduino/
//Limited to int max and min values.
void ftoa(float f, char *str, uint8_t precision=2) {
  char s1[10];
  
  memset(str, 0, sizeof(str));
  memset(s1, 0, sizeof(s1));
  
  if (f < 0) {                        //if a negative number 
    str[0] = '-';                     //start the char array with '-'
    f = abs(f);                       //store its positive absolute value
  }
  int8_t log_f = ceil(log10(f));             //get number of digits before the decimal
  int int_digits = (int)f;            //store the integer digits
  if (log_f > 0) {                    //log value > 0 indicates a number > 1
    if (precision == 0) {             //if number of digits = significant figures
      f += 0.5;                       //add 0.5 to round up decimals >= 0.5
      itoa(f, s1, 10);                //itoa converts the number to a char array
      strcat(str, s1);                //add to the number string
    }
    else {                            //if more precision specified than integer digits,
      itoa(int_digits, s1, 10);       //convert
      strcat(str, s1);                //and append
    }
  }

  else {                              //decimal fractions between 0 and 1: leading 0
    s1[0] = '0';
    strcat(str, s1);
  }

  if (precision > 0)
  {
    int digit = (int)f;
    float decimals = f - digit;             //get decimal value as float
    strcat(str, ".");                 //append decimal point to char array
    for (int j = 0; j < precision; j++) {         //for each,
      decimals *= 10.0;               //multiply decimals by 10      
      if (j == (precision-1) && ((decimals+0.5)<10)) decimals += 0.5;     //and if it's the last, add 0.5 to round it
      digit = (int)decimals;
      itoa(digit, s1, 10);            //convert as integer to character array
      strcat(str, s1);                //append to string
      decimals -= digit;              //and remove, moving to the next
    }
  }
}

//adapted from http://labdegaragem.com/profiles/blogs/convertendo-um-dado-float-para-string-no-arduino
//for ATMEL processors 26 to 72.09% slower for numbers smaller than 1000, 89 to 97% slower up to 10K and 119 to 143.48% above that
//for ARM processors 7 to 50% faster for numbers smaller than 1000, 1.3 to 10.4% slower up to 10K and 19 to 26% above that
void floatToString( float value, char *outstr, int places, int minwidth=0, bool rightjustify=false) {
    // this is used to write a float value to string, outstr.  oustr is also the return value.
    int digit;
    float tens = 0.1;
    int tenscount = 0;
    int i;
    float tempfloat = value;
    int c = 0;
    int extra = 0;
    int charcount;
    // make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
    // if this rounding step isn't here, the value  54.321 prints as 54.3209

    // calculate rounding term d:   0.5/pow(10,places)  
    float d = 0.5;
    if (value < 0)
        d *= -1.0;
    // divide by ten for each decimal place
    for (i = 0; i < places; i++)
        d/= 10.0;    
    // this small addition, combined with truncation will round our values properly 
    tempfloat +=  d;

    // first get value tens to be the large power of ten less than value    
    if (value < 0)
        tempfloat *= -1.0;
    while ((tens * 10.0) <= tempfloat) {
        tens *= 10.0;
        tenscount += 1;
    }

    if (tenscount > 0)
        charcount += tenscount;
    else
        charcount += 1;

    if (value < 0)
        charcount += 1;
    charcount += 1 + places;

    minwidth += 1; // both count the null final character
    if (minwidth > charcount){        
        extra = minwidth - charcount;
        charcount = minwidth;
    }

    if (extra > 0 and rightjustify) {
        for (int i = 0; i< extra; i++) {
            outstr[c++] = ' ';
        }
    }

    // write out the negative if needed
    if (value < 0)
        outstr[c++] = '-';

    if (tenscount == 0) 
        outstr[c++] = '0';

    for (i=0; i< tenscount; i++) {
        digit = (int) (tempfloat/tens);
        itoa(digit, &outstr[c++], 10);
        tempfloat = tempfloat - ((float)digit * tens);
        tens /= 10.0;
    }

    // if no places after decimal, stop now and return

    // otherwise, write the point and continue on
    if (places > 0)
    outstr[c++] = '.';


    // now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
    for (i = 0; i < places; i++) {
        tempfloat *= 10.0; 
        digit = (int) tempfloat;
        itoa(digit, &outstr[c++], 10);
        // once written, subtract off that digit
        tempfloat = tempfloat - (float) digit; 
    }
    if (extra > 0 and not rightjustify) {
        for (int i = 0; i< extra; i++) {
            outstr[c++] = ' ';
        }
    }


    outstr[c++] = '\0';
}

