#include "../stack/stack.h"
using namespace std;

class Postfix
{
  public:
    void Initial(char *str);
    bool IsDigit();
    Postfix();
    void MidToPostfix();
    bool Is_Operator(char op);/*判断是否为运算符*/
    int ISP(char op);//in stack priority
    int ICP(char op);//in coming priority
    char* GetPostExp();
    int StrLength(char* str);
    char* CreateString(char* str);
    void PrintMessage(char * message);
  private:
    SeqStack<char> *seqStack;
    char *postExp;
    char *midExp;
};

char* Postfix::CreateString(char* str)
{
  char* result=new char[StrLength(str)];
  char* temp=result;
  while(* temp++=* str++);
  return result;
}

Postfix::Postfix()
{
}

void Postfix::PrintMessage(char * message)
{
  cout<<message<<endl;
}

void Postfix::Initial(char *str)
{
  midExp=CreateString(str);
  postExp=new char[StrLength(str)];
  seqStack=new SeqStack<char>();
}

int Postfix::StrLength(char* str)
{
  int len=0;
  while(*str!='\0')
  {
    len++;
    str++;
  }
  return len;
}

void Postfix::MidToPostfix()
{
  char* midExpTemp=midExp;
  char* postExpTemp=postExp;
  seqStack->InitStack();
  seqStack->Push('#');
  while(*midExpTemp != '#')
  {
    if(isdigit(*midExpTemp) || isalpha(*midExpTemp))/*如果是数字或者字母复制，此处几乎没有什么问题*/ 
    {
      *postExpTemp++=*midExpTemp;
    }
    else if(Is_Operator(*midExpTemp))//如果是运算符
    {
      if(*midExpTemp==')')//如果是右括号
      {
        while(seqStack->StackTop()!='('&&!seqStack->StackEmpty())
        {
          *postExpTemp=seqStack->Pop();//运算符出栈	
          postExpTemp++;
        }
        seqStack->Pop();
      }
      else
      {
        if(ICP(*midExpTemp)>ISP(seqStack->StackTop()))//优先级大，入栈
        {
          seqStack->Push(*midExpTemp);//原先的运算符入栈	
        }
        else//优先级小，出栈
        {
          while(ICP(*midExpTemp)<ISP(seqStack->StackTop()))
          {
            *postExpTemp=seqStack->Pop();//运算符出栈	
            postExpTemp++;
          }
          seqStack->Push(*midExpTemp);//原先的运算符入栈	
        }	
      }
    }
    midExpTemp++;
  }
  while(seqStack->top)//复制剩下的
  {
    *postExpTemp++ = seqStack->Pop();
  }
  *postExpTemp = '\0';
}

int Postfix::ISP(char op)
{
  switch(op) 
  {
    case ')':
      return 8;     /*定义加减运算的优先级为1*/
    case '+': case '-':
      return 3;     /*定义加减运算的优先级为1*/
    case '*': case '/': case '%': 
      return 5;     /*定义乘除运算的优先级为2*/
    case '^': 
      return 7;     /*定义加减运算的优先级为3*/
    case '(': 
      return 1;     /*定义在栈中的左括号和栈底字符的优先级为0*/
    case '#': 
      return 0;     /*定义在栈中的左括号和栈底字符的优先级为0*/
  }
}

int Postfix::ICP(char op)
{
  switch(op) 
  {
    case ')':
      return 1;     /*定义加减运算的优先级为1*/
    case '+': case '-':
      return 2;     /*定义加减运算的优先级为1*/
    case '*': case '/': case '%': 
      return 4;     /*定义乘除运算的优先级为2*/
    case '^': 
      return 6;     /*定义加减运算的优先级为3*/
    case '(': 
      return 8;     /*定义在栈中的左括号和栈底字符的优先级为0*/
    case '#': 
      return 0;     /*定义在栈中的左括号和栈底字符的优先级为0*/
  }
}

bool Postfix::Is_Operator(char op)/*判断是否为运算符*/
{
  switch(op)
  {
    case'+': case'-': case'*': case'/': case '^':case '(':case ')':
      return true; 
    default:
      return false;
  }
}

char* Postfix::GetPostExp()
{
  return postExp;
}

int main()
{
  Postfix *postFix=new Postfix();
  postFix->Initial("A+B*(C-D)-E/F#");
  cout<<"the original string is:"<<endl<<"A+B*(C-D)-E/F#"<<endl;
  postFix->MidToPostfix();
  cout<<postFix->GetPostExp()<<endl;
  cout<<"the result should be:"<<endl<<"ABCD-*+EF/-"<<endl;
  return 0;
}
