/*
 * Course: COEN 2220 - Programming 2
 * Name: [Julian A. Pagan Hernandez]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic stack of active function calls
 * Due date: [10/23/2026]
 */

#include <iostream>
#include <string>
using namespace std;

class FunctionCallStack
{
private:
    // ===== Resolve these TODOs now (Part C) =====

    // TODO (Part C): Define Node with string functionName and Node *next.
    struct Node 
    {
        Node* next;
        string functionName;
    };
    // TODO (Part C): Declare Node *top for the node that must leave next.
    Node* top;

public:
    // TODO (Part C): Write a constructor that creates an empty stack.
    //Stack() = default; // Creates a empty stack
    FunctionCallStack() 
    {
        top = nullptr;
    }
    
    // ===== Resolve these TODOs later (Part D) =====

    // TODO (Part D): Write isEmpty as a const member function.
    bool isEmpty() const
    {
        return top == nullptr;    // Is going to return "top == nullptr
    }
    // TODO (Part D): Write push to add a function name at top.
   void push(string functionName)
    {
        Node *newNode = new Node;
        newNode->functionName = functionName;
        newNode->next = top;
        top = newNode;
    }
    // TODO (Part D): Write pop. It returns bool and uses string& removedFunctionName.
    bool pop(string& removedFunctionName)
    { 
        if (isEmpty())
        {
            return false;
        }
        
        removedFunctionName = top->functionName;
        Node *temp = top;
        top = top->next;
       // temp = nullptr;
        delete temp;
      

        return true;
    }
    

    // TODO (Part D): Write peek. It returns bool and uses string& topFunctionName.
    bool peek(string& topFunctionName) const
    {
        if (isEmpty())
        { 
            return false;
        }

        topFunctionName = top->functionName;
        return true;
    }

    // TODO (Part D): Write a destructor that releases every dynamic node.
    ~FunctionCallStack()
    {
        while(top != nullptr)
            {
                Node *temp = top;
                top = top->next;
                delete temp;
            }
    }
};

int main()
{
    cout << boolalpha;
  
    // ===== Resolve these TODOs later (Part D) =====

    // TODO (Part D): Create a FunctionCallStack object.
    FunctionCallStack callStacks;
    
    
    // TODO (Part D): Push main, loadSchedule, and formatSchedule in that order.
    callStacks.push("main");
    callStacks.push("loadSchedule");
    callStacks.push("formatSchedule");

    
    string name;
    // TODO (Part D): Use peek and pop to demonstrate LIFO with descriptive output.
    if (callStacks.peek(name))
    {    
         cout << "Top of the stack: " << name << endl;
    }

    while (callStacks.pop(name))
        {
            cout << "Returning from: " << name << endl;
        }    
    // TODO (Part D): Pop remaining calls, then demonstrate an unsuccessful pop on an empty stack.
    bool success = callStacks.pop(name);
    cout << "Pop on empty stack succeeded? " << success << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * D1 — Adding formatSchedule
 * When push("formatSchedule") executes, what must newNode->next receive before top
 * changes? Explain why reversing those two assignments would lose the previous top.
 * Answer:
 * newNode->next must receive the current top (which points to loadSchedule) before top changes. If top = newNode ran first, top would be overwritten and the address of the previous top node would be lost, so the existing nodes could no longer be reached and would leak memory.
 *
 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer:
 *    The three pops return formatSchedule, then loadSchedule, then main. This is LIFO (Last In, First Out): the most recently pushed call is the first one removed, just like functions return in the reverse order they were called.
 * 
 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer:
 *    The destructor must save the next-node address (move top to top->next) before deleting the current node, because once a node is deleted its memory is freed and its next pointer can no longer be safely read. Without saving it first, the rest of the list would be lost and reading freed memory is undefined behavior.
 */
