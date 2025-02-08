_____  
- Set **TIMER1_COMPA_vect** interrupt vector to the correponding ISR (_Interrupt Service Routine_)  
_____  
<image src=https://github.com/user-attachments/assets/531d7271-4a0e-44a3-8a1c-a4127b014768 width = 700/>
  
- Set **WGM12** bit of register **TCCR1B** for **CTC** (_Clear Timer on Compare match_) mode  
`TCCR1B |= (1 << WGM12);`  
_____  
<image src=https://github.com/user-attachments/assets/de0afe79-e7f8-433c-9c8c-170302f76575 width = 500/>  
  
- Set **CS10** and **CS12** bits of register **TCCR1B** for **prescaler = 1024**  
`TCCR1B |= (1 << CS12) | (1 << CS10);`
   
Use `(1<<CS11)` for **prescaler = 8**, `(1<<CS10)|(1<<CS11)` **for prescaler = 64**, `(1<<CS12)` for **prescaler = 256** as shown above  
_____  
 - Set **OCIE1A** bit of register **TIMSK1** to enable **Timer1** TCI (_Timer Compare Interrupt_)  
 `TIMSK1 |= (1 << OCIE1A);`
_____  
