#include <iostream>

using namespace std;

int main()
{
  short lim = 0, count;
  int mode = -1;

  while (lim <= 2)
  {
    cout << "ENTER SQRT LIMIT (>2) :";
    cin >> lim;
  }

  while (mode != 0 && mode != 1)
  {
    cout << "ENTER 0=EVEN 1=ODD :";
    cin >> mode;
  }

  if (mode == 0)
    count = 4;
  else
    count = 3;

  while (count <= lim)
  {
    short op = count;
    short res = 0;
    short one = 1 << 14; 

    while (one > op)
       one >>= 2;

    while (one != 0) //debugged to here
    {
      if (op >= res + one)
      {
        op -= res + one;
        res = (res >> 1) + one;
      }
      else
        res >>= 1;
      one >>= 2;
    }
    cout << "COUNT = " << count << endl;
    cout << "SQUARE ROOT = " << res << endl;
    count += 2;
  }

  return 0;
}
