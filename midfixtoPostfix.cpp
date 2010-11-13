#include "../stack/stack.h"
using namespace std;

class Postfix
{
  public:
    void Initial(char *str);
    bool IsDigit();
    Postfix();
    void MidToPostfix();
    bool Is_Operator(char op);/*�ж��Ƿ�Ϊ�����*/
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
    if(isdigit(*midExpTemp) || isalpha(*midExpTemp))/*��������ֻ�����ĸ���ƣ��˴�����û��ʲô����*/ 
    {
      *postExpTemp++=*midExpTemp;
    }
    else if(Is_Operator(*midExpTemp))//����������
    {
      if(*midExpTemp==')')//�����������
      {
        while(seqStack->StackTop()!='('&&!seqStack->StackEmpty())
        {
          *postExpTemp=seqStack->Pop();//�������ջ	
          postExpTemp++;
        }
        seqStack->Pop();
      }
      else
      {
        if(ICP(*midExpTemp)>ISP(seqStack->StackTop()))//���ȼ�����ջ
        {
          seqStack->Push(*midExpTemp);//ԭ�ȵ��������ջ	
        }
        else//���ȼ�С����ջ
        {
          while(ICP(*midExpTemp)<ISP(seqStack->StackTop()))
          {
            *postExpTemp=seqStack->Pop();//�������ջ	
            postExpTemp++;
          }
          seqStack->Push(*midExpTemp);//ԭ�ȵ��������ջ	
        }	
      }
    }
    midExpTemp++;
  }
  while(seqStack->top)//����ʣ�µ�
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
      return 8;     /*����Ӽ���������ȼ�Ϊ1*/
    case '+': case '-':
      return 3;     /*����Ӽ���������ȼ�Ϊ1*/
    case '*': case '/': case '%': 
      return 5;     /*����˳���������ȼ�Ϊ2*/
    case '^': 
      return 7;     /*����Ӽ���������ȼ�Ϊ3*/
    case '(': 
      return 1;     /*������ջ�е������ź�ջ���ַ������ȼ�Ϊ0*/
    case '#': 
      return 0;     /*������ջ�е������ź�ջ���ַ������ȼ�Ϊ0*/
  }
}

int Postfix::ICP(char op)
{
  switch(op) 
  {
    case ')':
      return 1;     /*����Ӽ���������ȼ�Ϊ1*/
    case '+': case '-':
      return 2;     /*����Ӽ���������ȼ�Ϊ1*/
    case '*': case '/': case '%': 
      return 4;     /*����˳���������ȼ�Ϊ2*/
    case '^': 
      return 6;     /*����Ӽ���������ȼ�Ϊ3*/
    case '(': 
      return 8;     /*������ջ�е������ź�ջ���ַ������ȼ�Ϊ0*/
    case '#': 
      return 0;     /*������ջ�е������ź�ջ���ַ������ȼ�Ϊ0*/
  }
}

bool Postfix::Is_Operator(char op)/*�ж��Ƿ�Ϊ�����*/
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
