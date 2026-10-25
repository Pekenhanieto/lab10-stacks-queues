/*
 * Course: COEN 2220 - Programming 2
 * Name: [Julian A. Pagan Hernandez]
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic queue of tutoring requests
 * Due date: [10/23/2026]
 */

#include <iostream>
#include <string>
using namespace std;

class TutoringQueue
{
private:
    struct Node
    {
        string studentId; // Store one student waiting for tutoring.
        Node *next;       // Point to the student immediately behind this one.
    };

    Node *front; // Point to the student who must be served next.
    Node *rear;  // Point to the student most recently added.

public:
    TutoringQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~TutoringQueue()
    {
        while (front != nullptr)
        {
            Node *nodeToDelete = front;
            front = front->next; // Advance before releasing the current node.
            delete nodeToDelete;
        }

        rear = nullptr;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    // ===== Resolve these TODOs now (Part E) =====

    // TODO (Part E): Write enqueue to add newStudentId at rear.
    void enqueue(const string &newStudentId)
    {
        Node *newNode = new Node;
        newNode->studentId = newStudentId;
        newNode->next = nullptr; // The new student begins as the last node.

        if (rear == nullptr)
        {
            front = newNode; // The first node is also the front.
            rear = newNode;  // The first node is also the rear.
            return;
        }

        rear->next = newNode; // Connect the old rear to the new node.
        rear = newNode;       // The new node becomes the rear.
    }
    // TODO (Part E): Write dequeue. It returns bool and uses string& servedStudentId.
    bool dequeue(string &servedStudentId)
    {
        if (front == nullptr)
        {
            return false; // The queue is empty, nothing to dequeue.
        }

        Node *nodeToDelete = front;
        servedStudentId = front->studentId;
        front = front->next; // The next student becomes the front.

        if (front == nullptr)
        {
            rear = nullptr; // Removing the last node leaves both pointers empty.
        }

        delete nodeToDelete;
        return true;
    }
};

int main()
{
    cout << boolalpha;

    // TODO (Part E): Create a TutoringQueue object.
    TutoringQueue queue;
    // TODO (Part E): Add TU-301, TU-318, and TU-327 in that arrival order.
    queue.enqueue("TU-301");
    queue.enqueue("TU-318");
    queue.enqueue("TU-327");
    // TODO (Part E): Dequeue and print the first two served student IDs.
    string studentId;
    if (queue.dequeue(studentId))
    {
        cout << "Served student ID: " << studentId << endl;
    }
    if (queue.dequeue(studentId))
    {
        cout << "Served student ID: " << studentId << endl;
    }
    // TODO (Part E): Dequeue the last student, then print whether the queue is empty.
    if (queue.dequeue(studentId))
    {
        cout << "Served student ID: " << studentId << endl;
    }
    cout << "Is the queue empty? " << queue.isEmpty() << endl;
    // TODO (Part E): Add TU-340 after the queue becomes empty, dequeue it, and print its ID.
    queue.enqueue("TU-340");
    if (queue.dequeue(studentId))
    {
        cout << "Served student ID: " << studentId << endl;
    }

    return 0;
}

/*
 * Analysis Answers
 *
 * E1 — First arrival
 * Why must the first call to enqueue assign newNode to both front and rear?
 * Answer:
 * The first node added to the queue becomes both the first and last node, so both pointers must reference it.
 *
 * E2 — Last departure
 * After dequeue removes the only remaining node, what must happen to rear and why?
 * Answer:
 * The rear pointer must be set to nullptr because there are no more nodes in the queue.
 * E3 — FIFO evidence
 * List the expected service order for TU-301, TU-318, and TU-327. Explain why this
 * differs from the return order of the function-call stack in Part D.
 * Answer:
 *  The expected service order is TU-301, TU-318, TU-327. This differs from the LIFO order of a stack because a queue operates on a FIFO basis, serving the first student who arrived first.
 */