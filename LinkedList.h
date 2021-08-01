#include <iostream>
#include <functional>
#include <cstdarg>

using namespace std;

/* Node structure */
struct Node
{
    int data;
    Node *next;
};

struct Head
{
    Node *next;
};

/*
LinkedList is a simulation of a mutable array, made with a linked list.

Usage:
    To define the linked list, make an object of this class and pass the values as such:
    LinkedList linList(<number of arguments you are going to pass>, <n amount of arguments, seperated by a comma>);


Examples:
    LinkedList linList(2, 4, 6);
    LinkedList linList(1, 9);
    LinkedList linList(5, 3, 6, 3, 8, 9);

!!!Parameters in [] are optional.

LinkedList::valueOnIndex(int index)
LinkedList::push(int nodeValue)
LinkedList::append(int nodeValue)
LinkedList::appendAtIndex(int index, int nodeValue)
LinkedList::pop()
LinkedList::remove(int index)
LinkedList::removeAllOccurrences(int value)
LinkedList::clear()
LinkedList::size()
LinkedList::shift()
LinkedList::join([string seperator])
LinkedList::concat(LinkedList list)
LinkedList::length()
LinkedList::countAllOccurrences(int value)
LinkedList::TraverseLinkedList()
LinkedList::reverse()
LinkedList::forEach(Node node, int index) <- need to make better
LinkedList::firstOccurrence(int value)
LinkedList::removeDuplicatesOfValue(int value)
LinkedList::removeDuplicates()

TODO:

LinkedList::sort()
LinkedList::removeMultiple()
LinkedList::expand(LinkedList list)
LinkedList::change(int index, int value)
LinkedList::value -> returns an array of values
*/
class LinkedList
{
public:
    LinkedList(int numArgs, ...)
    {
        head->next = NULL;
        if (numArgs == 0)
        {
            return;
        }
        va_list valist;
        va_start(valist, numArgs);
        for (int i = 0; i < numArgs; i++)
        {
            append(va_arg(valist, int));
        }
        va_end(valist);
    }

    /* Gives the node value on given index. */
    int valueOnIndex(int index)
    {
        Node *temp = head->next;
        int arr[length()];

        if (index > length() || index < 0)
        {
            return -1;
        }

        for (int i = 0; i < length(); i++)
        {
            arr[i] = temp->data;
            temp = temp->next;
        }

        return arr[index];
    }

    /* Appends a node with the given value on the start of the list. */
    /*     void push(int nodeValue)
    {
        struct Node *insertNode = new Node();

        insertNode->data = head->data;
        insertNode->next = head->next;
        head->data = nodeValue;
        head->next = insertNode;
    } */

    /* Appends a node with the given value on the end of the list. */
    void append(int nodeValue)
    {
        struct Node *insertNode = new Node();
        insertNode->data = nodeValue;
        insertNode->next = NULL;
        if (head->next == NULL)
        {
            head->next = insertNode;
            return;
        }
        struct Node *temp = head->next;
        insertNode->data = nodeValue;
        insertNode->next = NULL;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = insertNode;
    }

    /* Appends node at index. */
    void appendAtIndex(int index, int nodeValue)
    {
        if (index > length() || index < 0)
        {
            return;
        }
        struct Node *temp = head->next;
        struct Node *insertNode = new Node();

        insertNode->data = nodeValue;

        if (index == 0)
        {
            insertNode->next = head->next;
            head->next = insertNode;
            return;
        }

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        insertNode->next = temp->next;
        temp->next = insertNode;
    }

    /* Removes the last element in the list and returns it. */
    Node *pop()
    {
        return remove(length() - 1);
    }

    /* Removes the element at the given index and returns it. */
    Node *remove(int index)
    {
        struct Node *returnNode = new Node();
        struct Node *temp = head->next;

        if (index == 0)
        {
            returnNode = head->next;
            head->next = head->next->next;
            return returnNode;
        }
        else if (index < 0 || index > length())
        {
            return temp;
        }

        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }

        returnNode = temp->next;
        temp->next = temp->next->next;

        return returnNode;
    }

    /* Removes the first element from array and returns it. */
    Node *shift()
    {
        return remove(0);
    }

    /* Removes all occurrences of the given value and returns the given value. */
    int removeAllOccurrences(int value)
    {
        struct Node *temp = head->next;
        int index = 0;

        while (temp != NULL)
        {
            if (temp->data == value)
            {
                remove(index);
            }
            else
            {
                index++;
            }
            temp = temp->next;
        }

        return value;
    }

    /* Removes all duplicates from the list while only keeping the first occurrece of each.  */ // WIP
    void removeDuplicates()
    {
        bool removed = false;
        for (int i = 0; i < length(); i++)
        {
            if (countAllOcurrences(valueOnIndex(i)) > 1)
            {
                removeDuplicatesOfValue(valueOnIndex(i));
            }
        }
    }

    /* Removes all occurrences of the given value, except the first one. */
    void removeDuplicatesOfValue(int value)
    {
        bool first = true;
        struct Node *temp = head->next;
        int index = 0;

        while (temp != NULL)
        {
            if (temp->data == value)
            {
                if (first == false)
                {
                    remove(index);
                }
                else
                {
                    first = false;
                    index++;
                }
            }
            else
            {
                index++;
            }
            temp = temp->next;
        }
    }

    /* Removes all elements from list. */
    void clear()
    {
        int times = length();
        for (int i = 0; i < times; i++)
        {
            pop();
        }
    }

    /* Returns the size of the list in bytes.

    Expression: this.length() * sizeof(new Node) + sizeof(new Head);
     */
    int size()
    {
        return length() * sizeof(new Node) + sizeof(new Head);
    }

    /* Returns the number of nodes in the Linked List. */
    int length()
    {
        struct Node *temp = head->next;
        int length = 0;

        while (temp != NULL)
        {
            ++length;
            temp = temp->next;
        }

        return length;
    }

    /* Returns the number of all ocurrences of the given value in the list. */
    int countAllOcurrences(int value)
    {
        int occurrences = 0;

        for (int i = 0; i < length(); i++)
        {
            if (valueOnIndex(i) == value)
            {
                occurrences++;
            }
        }
        return occurrences;
    }

    /* Prints the list values to the console. */
    void TraverseLinkedList()
    {
        struct Node *temp = head->next;

        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    string join(string seperator = " ") // TODO
    {
        string returnStr = "";
        for (int i = 0; i < length(); i++)
        {
            returnStr.append(to_string(valueOnIndex(i)) + seperator);
        }

        return returnStr;
    }

    /* Reverses the linked list. */
    void reverse()
    {
        struct Node *current = head->next;
        struct Node *prev = NULL, *next = NULL;

        while (current != NULL)
        {
            next = current->next;

            current->next = prev;
            prev = current;
            current = next;
        }
        head->next = prev;
    }

    /* Returns a object of type LinkedList. Concatinates two lists. */
    LinkedList concat(LinkedList list)
    {
        LinkedList tempList(0);
        tempList.expand(thisList());
        tempList.expand(list);
        return tempList;
    }

    /* Expands the list with the given list. */
    void expand(LinkedList list)
    {
        for (int i = 0; i < list.length(); i++)
        {
            append(list.valueOnIndex(i));
        }
    }

    /* Executes the given lambda expression for each element in the linked list. */
    int forEach(const function<int(Node *, int index)> &f)
    {
        struct Node *temp = head->next;

        for (int i = 0; i < length(); i++)
        {
            f(temp, i);
            temp = temp->next;
        }

        return 0;
    }

    /* Returns the index of the first occurrence of the value. If the value isn't in the list the return value is -1. */
    int firstOccurrence(int value)
    {
        struct Node *temp = head->next;
        int index = 0;

        while (temp != NULL)
        {
            if (temp->data == value)
            {
                return index;
            }
            temp = temp->next;
            index++;
        }

        return -1;
    }

private:
    struct Head *head = new Head();

    LinkedList thisList()
    {
        LinkedList tempList(0);
        for (int i = 0; i < length(); i++)
        {
            tempList.append(valueOnIndex(i));
        }
        return tempList;
    }
};