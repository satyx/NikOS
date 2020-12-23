#include <keyboard.h>
#include <isr.h>
#include <stdio.h>
char keys[256] = 
{'*', '*', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '*', 'a', 's',
'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '*', '\\', 'z', 'x', 'c', 'v',
'b', 'n', 'm', ',', '.', '/', '*', '*', '*', ' ', '*', '*', '*', '*', '*', '*',
'*', '*', '*', '*', '*', '*', '*', '7', '8', '9', '-', '4', '5', '6', '+', '1',
'2', '3', '0', '.'};//, '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'};

char upper_keys[256] = 
{'*', '*', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', '*', 'A', 'S',
'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', '*', '|', 'Z', 'X', 'C', 'V',
'B', 'N', 'M', '<', '>', '?', '*', '*', '*', ' ', '*', '*', '*', '*', '*', '*',
'*', '*', '*', '*', '*', '*', '*', '7', '8', '9', '-', '4', '5', '6', '+', '1',
'2', '3', '0', '.'};//, '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
// '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'};

bool is_alphabet(const unsigned char ch)
{
  return ((ch>=16 && ch<=25)||(ch>=30 && ch<=38)||(ch>=44 && ch<=50));
}

bool is_function_key(const unsigned char ch)
{

  return ((ch>=0x3B && ch<=0x44)||(ch==0x57)||(ch==0x58));
}
bool is_keypad(const unsigned char ch)
{
  return (ch>=0x47 && ch<=0x53);
}

bool is_displayable(const unsigned char ch)
{
  return !((ch==CAPS)||(ch==LEFT_SHIFT)||(ch==RIGHT_SHIFT)||(ch==CTRL)||(ch==ALT)||(ch==ESC)||is_function_key(ch)||(ch==NUMBER_LOCK));
}

void keyb_callback(registers_t regs)
{
  static bool shift_flag = false;
  static bool caps_flag = false;
  static bool alt_flag = false;
  static bool ctrl_flag = false;
  static bool special_flag = false;
  static bool number_lock_flag = false;

  unsigned char scancode = inb(0x60);
  
  if(scancode==SPECIAL)
  {
    special_flag = true;
    return;
  }

  if(scancode & 0x80)
  {
    if(scancode==LEFT_SHIFT+RELEASED_OFFSET || scancode==RIGHT_SHIFT+RELEASED_OFFSET)
      shift_flag=false;
    else if(scancode==CTRL + RELEASED_OFFSET)
      ctrl_flag = false;
    else if(scancode==ALT + RELEASED_OFFSET)
      alt_flag = false;
  }
  
  else
  {
    if(is_displayable(scancode))
    {
      if(is_alphabet(scancode))
      {
        if(shift_flag^caps_flag)
          putchar(upper_keys[scancode]);
        else
          putchar(keys[scancode]);
      }
      else
      {
        if(is_keypad(scancode))
        {
          if((number_lock_flag^shift_flag)&&(!special_flag))
            putchar(keys[scancode]);
        }
        else
        {
          if(shift_flag)
            putchar(upper_keys[scancode]);
          else
            putchar(keys[scancode]);
        }
      }
    }
    else
    {
      if(scancode==LEFT_SHIFT || scancode==RIGHT_SHIFT)
        shift_flag = true;
      else if(scancode == CTRL)
        ctrl_flag = true;
      else if(scancode == ALT)
        alt_flag = true;
      else if(scancode == CAPS)
        caps_flag ^= 1;
      else if(scancode == NUMBER_LOCK)
        number_lock_flag ^= 1;  
    }
  }
  special_flag = false;
}

void init_keyboard()
{
   register_interrupt_handler(IRQ1, &keyb_callback);

   outb(0x21, 0x60);
   outb(0x21, 0x64);

}