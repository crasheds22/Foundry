#include "ManagerTest.h"

bool ManagerTest::Test()
{
    bool allPassed = false;

    allPassed = ManagerForInts();
    std::cout << std::endl;
    allPassed = ManagerForIntegers();

    return allPassed;
}

bool ManagerTest::ManagerForInts()
{
    Resource::Manager<int> IntManager;

    std::cout << "Inserting <One, 1>...<Ten, 10>" << std::endl;

    IntManager.Create("One", 1);
    IntManager.Create("Two", 2);
    IntManager.Create("Three", 3);
    IntManager.Create("Four", 4);
    IntManager.Create("Five", 5);
    IntManager.Create("Six", 6);
    IntManager.Create("Seven", 7);
    IntManager.Create("Eight", 8);
    IntManager.Create("Nine", 9);
    IntManager.Create("Ten", 10);

    std::cout << "Retrieving \"Five\": " << *IntManager.Retrieve("Five") << std::endl;

    return *IntManager.Retrieve("Six") == 6;
}

bool ManagerTest::ManagerForIntegers()
{
    Resource::Manager<Integer> IntegerManager;

    std::cout << "Inserting Integer class types <One, 1>...<Ten, 10>" << std::endl;

    IntegerManager.Create("One"     , Integer(1));
    IntegerManager.Create("Two"     , Integer(2));
    IntegerManager.Create("Three"   , Integer(3));
    IntegerManager.Create("Four"    , Integer(4));
    IntegerManager.Create("Five"    , Integer(5));
    IntegerManager.Create("Six"     , Integer(6));
    IntegerManager.Create("Seven"   , Integer(7));
    IntegerManager.Create("Eight"   , Integer(8));
    IntegerManager.Create("Nine"    , Integer(9));
    IntegerManager.Create("Ten"     , Integer(10));

    std::cout << "Retrieving \"Four\": " << IntegerManager.Retrieve("Four")->Int() << std::endl;
    std::cout << "Retrieving \"Seven\": " << IntegerManager.Retrieve("Seven")->Int() << std::endl;

    return IntegerManager.Retrieve("Ten")->Int() == 10;
}

Integer::Integer(int i)
{
    mInt = i;
}

int Integer::Int() const
{
    return mInt;
}
