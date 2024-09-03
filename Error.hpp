/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Errors.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include "Error.h"
#if SEAM >= SCRIPT2_LIST
namespace _ {
  
/* An array of CrabsError strinsg as an array of CH[AErrorCountMax][32].
Example: const CHA* error_6 = TCrabsError
0000000000000000000000
Generic error000000000
Authentication error00
Array overflow00000000
Buffer overflow0000000
Buffer underflow000000
Keys buffer overflow00
Input invalid000000000
Input nil0000000000000
Invalid args0000000000
Invalid argument000000
Invalid buffer00000000
Invalid door0000000000
Invalid error handler0
Invalid header00000000
Invalid hash0000000000
Invalid index000000000
Invalid inquiry0000000
Invalid op000000000000
Invalid operand0000000
Invalid Room number000
Invalid type0000000000
Invalid UTF-8000000000
Invalid UTF-1600000000
Invalid UTF-3200000000
Read only0000000000000
Write only000000000000
Parameter overflow0000
Stack overflow00000000
Stack underflow0000000
Text overflow000000000
Varint overflow0000000
Implementation error00
*/
template<typename CH = CHR>
const CH* TErrorST() {
  static const CH error_strings[CrabsErrorCount][32] = {
    /*00*/{'S','u','c','k',' ','i','t',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    /*01*/{'G','e','n','e','r','i','c',' ','e','r','r','o','r',0,0,0,0,0,0,0,0,
           0},
    /*02*/{'A','u','t','h','e','n','t','i','c','a', 't','i','o','n',
           ' ','e','r','r','o','r',0,0},
    /*03*/{'A','r','r','a','y',' ','o','v','e','r','f','l','o','w',0,0,0,0,0,0,
           0,0},
    /*04*/{'B','u','f','f','e','r',' ','u','n','d','e','r','f','l','o','w',0,0,
           0,0,0,0},
    /*05*/{'B','u','f','f','e','r',' ','o','v','e','r','f','l','o','w',0,0,0,0,
           0,0,0},
    /*06*/{'K', 'e', 'y', 's', ' ', 'b', 'u', 'f', 'f', 'e', 'r', ' ', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w', 0, 0 },
    /*07*/{'I','n','p','u','t',' ','i','n','v','a','l','i','d',0,0,0,0,0,0,0,0,
           0},
    /*08*/{'I','n','p','u','t',' ','n','i','l',0,0,0,0,0,0,0,0,0,0,0,0,0},
    /*09*/{'I','n','v','a','l','i','d',' ','a','r','g','s',0,0,0,0,0,0,0,0,0,0},
    /*10*/{'I','n','v','a','l','i','d',' ','a','r','g','u','m','e','n','t',0,0,
           0,0,0,0},
    /*11*/{'I','n','v','a','l','i','d',' ','b','u','f','f','e','r',0,0,0,0,0,0,
           0,0},
    /*12*/{'I','n','v','a','l','i','d',' ','d','o','o','r',0,0,0,0,0,0,0,0,0,0},
    /*13*/{'I','n','v','a','l','i','d',' ','e','r','r','o','r',' ','h','a','n',
           'd','l','e','r',0},
    /*14*/{'I','n','v','a','l','i','d',' ','h','e','a','d','e','r',0,0,0,0,0,0,
           0,0},
    /*15*/{'I','n','v','a','l','i','d',' ','h','a','s','h',0,0,0,0,0,0,0,0,0,0},
    /*16*/{'I','n','v','a','l','i','d',' ','i','n','d','e','x',0,0,0,0,0,0,0,0,
           0},
    /*17*/{'I','n','v','a','l','i','d',' ','i','n','q','u','i','r','y',0,0,0,0,
           0,0,0},
    /*18*/{'I','n','v','a','l','i','d',' ','o','p',0,0,0,0,0,0,0,0,0,0,0,0},
    /*19*/{'I','n','v','a','l','i','d',' ','o','p','e','r','a','n','d',0,0,0,0,
           0,0,0},
    /*20*/{'I','n','v','a','l','i','d',' ','R','o','o','m',' ','n','u','m','b',
           'e','r',0,0,0},
    /*21*/{'I','n','v','a','l','i','d',' ','t','y','p','e',0,0,0,0,0,0,0,0,0,0},
    /*22*/{'I','n','v','a','l','i','d',' ','U','T','F','-','8',0,0,0,0,0,0,0,0,
           0},
    /*23*/{'I','n','v','a','l','i','d',' ','U','T','F','-','1','6',0,0,0,0,0,0,
           0,0},
    /*24*/{'I','n','v','a','l','i','d',' ','U','T','F','-','3','2',0,0,0,0,0,0,
           0,0},
    /*25*/{'R', 'e', 'a', 'd', ' ', 'o', 'n', 'l', 'y', 0, 0, 0, 0, 0, 0, 0, 0, 
           0, 0, 0, 0, 0},
    /*26*/{'W', 'r', 'i', 't', 'e', ' ', 'o', 'n', 'l', 'y', 0, 0, 0, 0, 0, 0, 
           0, 0, 0, 0, 0, 0 },
    /*27*/{'P','a','r','a','m','e','t','e','r',' ','o','v','e','r','f','l','o',
           'w',0,0,0,0},
    /*28*/{'S','t','a','c','k',' ','o','v','e','r','f','l','o','w',0,0,0,0,0,0,
           0,0},
    /*29*/{'S','t','a','c','k',' ','u','n','d','e','r','f','l','o','w',0,0,0,0,
           0,0,0},
    /*30*/{'T','e','x','t',' ','o','v','e','r','f','l','o','w',0,0,0,0,0,0,0,0,
           0},
    /*31*/{'V','a','r','i','n','t',' ','o','v','e','r','f','l','o','w',0,0,0,0,
           0,0,0},
    /*32*/{'I','m','p','l','e','m','e','n','t','a','t','i','o','n',' ','e','r',
           'r','o','r',0,0}
  };
  return &error_strings[0][0];
}

template<typename CH = CHR, typename IS = ISQ>
const CH* TErrorST(IS index) {
  if (index < 0) index *= -1;
  if (index >= CrabsErrorCount) index = CrabsErrorCount;
  return &TErrorST<CH>()[index << 5];
}
}  //< namespace _
#endif
