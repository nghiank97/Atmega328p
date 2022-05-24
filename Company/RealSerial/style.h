
#ifndef STYLE_H
#define STYLE_H

#define sbi(PORT,PIN)                               (PORT |= (1<<PIN))
#define cbi(PORT,PIN)                               (PORT &= ~(1<<PIN))
#define bv(PIN)                                     (1<<PIN)
#define bit_is_clear(PORT,PIN)                      (!(PORT&(1<<PIN)))
#define bit_is_set(PORT,PIN)                        (PORT&(1<<PIN))

#endif
