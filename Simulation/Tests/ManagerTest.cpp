#include "ManagerTest.h"

bool ManagerTest::Test()
{
    bool allPassed = false;

    allPassed = ManagerForInts();

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
