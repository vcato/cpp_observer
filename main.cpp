#include <functional>
#include <cassert>
#include <set>
#include <memory>
#include "observer.hpp"


static void testNormalUsage()
{
  int data = 5;
  Subject<int> subject(data);
  subject.setData(6);
  int change1 = 0;
  Observer<int> observer1(subject,[&](){ ++change1; });
  subject.setData(7);
  assert(change1==1);
  int change2 = 0;
  Observer<int> observer2(subject,[&](){ ++change2; });
  subject.setData(8);
  assert(change1==2);
  assert(change2==1);
}


static void testWhenSubjectIsDestroyedBeforeObserver()
{
  int data = 5;
  std::unique_ptr<Observer<int>> observer_ptr;
  {
    Subject<int> subject(data);
    observer_ptr = std::make_unique<Observer<int>>(subject,[](){});
  }
  assert(!observer_ptr->hasSubject());
}


int main()
{
  testNormalUsage();
  testWhenSubjectIsDestroyedBeforeObserver();
}
