#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

template <typename Data>
struct Subject {
  public:
    class Observer;

    Subject(Data &data_arg);
    ~Subject();

    void setData(Data arg);

  private:
    Data &data;
    std::set<Observer*> observers;
};


template <typename Data>
class Subject<Data>::Observer {
  public:
    Observer(Subject &subject,std::function<void()> callback_arg);
    ~Observer();

    bool hasSubject() const;

  private:
    friend class Subject;

    Subject *subject_ptr;
    std::function<void()> callback;
};


template <typename Data>
using Observer = typename Subject<Data>::Observer;


/// Implementation Below
/////////////////////////


template <typename Data>
Subject<Data>::Subject(Data &data_arg)
: data(data_arg)
{
}


template <typename Data>
Subject<Data>::~Subject()
{
  for (auto observer_ptr : observers) {
    assert(observer_ptr);
    observer_ptr->subject_ptr = nullptr;
  }
}


template <typename Data>
void Subject<Data>::setData(Data arg)
{
  data = arg;

  for (auto observer_ptr : observers) {
    assert(observer_ptr);
    observer_ptr->callback();
  }
}


template <typename Data>
Subject<Data>::Observer::Observer(
  Subject &subject,std::function<void()> callback_arg
)
: subject_ptr(&subject), callback(std::move(callback_arg))
{
  subject.observers.insert(this);
}


template <typename Data>
Subject<Data>::Observer::~Observer()
{
  if (subject_ptr) {
    subject_ptr->observers.erase(this);
  }
}


template <typename Data>
bool Subject<Data>::Observer::hasSubject() const
{
  return subject_ptr;
}


#endif /* OBSERVER_HPP_ */
