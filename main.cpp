#include <QObject>
#include <iostream>
class Counter:public QObject
{
Q_OBJECT
public:
Counter(int start_value,const std::string &the_name,
QObject *base=nullptr):m_count(
start_value),name_of_emitter(the_name),QObject(base)
{
std::cout<<"Hi! I am "+name_of_emitter+" and my start value is "+
           std::to_string(m_count)+"!"<<std::endl;
}
void Increment()
{
++m_count;
std::cout<<"I am "+name_of_emitter+
           "! I incremented myself! My current count is "
+std::to_string(m_count)+"!"<<std::endl;
emit IncrementOther(name_of_emitter);
}
void Decrement()
{
--m_count;
std::cout<<"I am "+name_of_emitter+
               "! I decremented myself! My current count is "
+std::to_string(m_count)+"!"<<std::endl;
emit DecrementOther(name_of_emitter);
}
signals:
void IncrementOther(const std::string &who_incremented);
void DecrementOther(const std::string &who_decremented);
public slots:
void ReceiveIncrementSignal(const std::string &who_incremented)
{
++m_count;
std::cout<<"I am "<<name_of_emitter+ "! "
           +who_incremented+" incremented me! My current count is "+
           std::to_string(m_count)+"!"<<std::endl;
}
void ReceiveDecrementSignal(const std::string &who_decremented)
{
--m_count;
std::cout<<"I am "<<name_of_emitter+ "! "
           +who_decremented+" decremented me! My current count is "+
           std::to_string(m_count)+"!"<<std::endl;
}
private:
int m_count;
const std::string name_of_emitter;
};
int main(int argc, char *argv[])
{
    Counter Alex(33,"Alex"),
            Nicholas(11,"Nicholas");
    QObject::connect(&Alex,&Counter::IncrementOther,&Nicholas,
                     &Counter::ReceiveIncrementSignal);
    QObject::connect(&Alex,&Counter::DecrementOther,&Nicholas,
                     &Counter::ReceiveDecrementSignal);
    QObject::connect(&Nicholas,&Counter::IncrementOther,&Alex,
                     &Counter::ReceiveIncrementSignal);
    QObject::connect(&Nicholas,&Counter::DecrementOther,&Alex,
                     &Counter::ReceiveDecrementSignal);
    Alex.Increment();
    Nicholas.Increment();
    return 0;
}
#include "main.moc"
