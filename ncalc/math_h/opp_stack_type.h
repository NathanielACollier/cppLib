/*
Nathaniel Collier
8/12/2006
Opperation Stack Type
*/



#ifndef OPP_STACK_TYPE
#define OPP_STACK_TYPE


class op_value
{
 private:
    char op_text;     // operator value
    int order;
 public:
    op_value();
    void set_operator( char op );
    void clear();
    char get_operator(){ return op_text; }
    int get_order(){ return order; }
};

op_value::op_value()
{
 // constructor
 op_text = '0';
 order = 0;
}



void op_value::set_operator( char op )
{
 op_text = op;
 switch( op )
 {
 case '+': order = 0; break;
 case '-': order = 0; break;
 case '*': order = 1; break;
 case '/': order = 1; break;
 case '^': order = 2; break;
 case ')': order = 3; break;
 case '(': order = 3; break;
 default: order = 0; break;
 }
}

void op_value::clear()
{
 op_text = '0';
}


#endif
