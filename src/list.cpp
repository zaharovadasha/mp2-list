#include "list.h"

#include "list.h"

Node::Node()
{
	data = NULL;
	next = NULL;
}

Node::Node(DataType _f, Node *_n)
{
	data = _f;
	next = _n;
}

Node::Node(const Node &node2)
{
	data = node2.data;
	next = node2.next;
}

Node Node::operator=(const Node &node2)
{
	data = node2.data;
	next = node2.next;
	return *this;
}

bool Node::operator==(const Node &node2) const
{
	if ((data != node2.data)&& (next == node2.next))
		return false;
	else return true;
}

List::List(const List& list2)
{
	if (list2.unit != NULL)
	{
		unit = new Node(list2.unit->data, list2.unit->next);
		Node* temp1 = unit;
		Node *temp2 = list2.unit->next;
		while (temp2->next != NULL)
		{
			temp1->next = new Node(temp1->data, temp1->next);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
	else unit = NULL;
}

List& List::operator=(const List& list2)
{
	if (unit != list2.unit)
	{
		Clean();
		if (list2.unit == NULL)
		{
			unit = list2.unit;
			return *this;
		}
		else
		{
			unit = new Node(list2.unit->data, list2.unit->next);
			Node *a1 = unit;
			Node *a2 = list2.unit;
			while (a2 != NULL)
			{
				a1 = new Node(a2->data, a2->next);
				a1 = a1->next;
				a2 = a2->next;
			}
		}
	}
	return *this;
}

void List::InsertToHead(const DataType & d)
{
	Node *a = new Node(d, unit); 
	a->next = unit;
	unit = a;
}

void List::InsertToTail(const DataType& d)
{
	Node *a = unit;
	if (a)
	{
		while (a->next)
			a = a->next;
		a->next = new Node(d, NULL);
	}
	else
		unit = new Node(d, NULL);
}

void List::InsertAfter(Node* node, const DataType& d) // вставить элемент d после звена node
{
	if (unit != NULL)
	{
		Node *a;
		a = new Node(d, node->next);
		node->next = a;
	}
	else
		throw "Error";
};

void List::Delete(const DataType & d)
{
	Node *a = unit;
	Node *temp;
	if (unit)
	{
		if (unit->data == d)
		{
			temp = a->next;
			delete unit;
			unit = temp;
		}
		else
		{
			while (a->next)
			{
				if (a->next->data == d)
				{
					temp = a->next;
					break;
				}
				a = a->next;
			}
			if (a->next)
			{
				a->next = temp->next;
				delete temp;
			}
		}
	}
}

Node* List::Search(const DataType& d)
{
	Node *a = unit;
	while (a)
	{
		if (a->data == d)
			return a;
		a = a->next;
	}
	return NULL;
}

void List::Del()
{
	Node *a = unit;
	while (a->next != NULL)
	{
		Node * temp = a->next;
		delete a;
		a = temp;
	}
}

void List::Clean()
  {
	  if (unit == NULL)
		  return;
	  Node *a = unit, *n;
	  while (a->next != NULL)
	  {
		  n = a->next->next;
		  delete a->next;
		  a->next = n;
	  }
	  delete a;
	  unit = NULL;
  }

int List::GetSize()
{
	int k = 0;
	Node *a = unit;

	while (a != NULL)
	{
		k++;
		a = a->next;
	}

	return k;
}

void List::Inverse()
{
	if (unit)
	{
		Node *a1, *a2, *a3;
		a1 = unit;
		a2 = unit->next;
		a1->next = NULL;
		while (a2 != NULL)
		{
			a3 = a2->next;
			a2->next = a1;
			a1 = a2;
			a2 = a3;
		}
		unit = a1;
	}
}

List List::Merge(Node* node, const List& list2)
  {
	  if (unit != NULL)
	  {
		  List list3;
		  list3.unit = new Node(unit->data, NULL);
		  Node *a1 = list3.unit;
		  Node *a2 = unit;
		  
		  while ((a2->next!=NULL) && (a2 != node))
		  {
			  a1->next = new Node(a2->next->data, NULL);
			  a1 = a1->next;
			  a2 = a2->next;
		  }
		  if (node != NULL)
		  {
			  Node *a3 = list2.unit;
			  while (a3 != NULL)
			  {
				  a1->next = new Node(a3->data,NULL);
				  a1 = a1->next;
				  a3 = a3->next;
			  }
			  while (a2->next!=NULL)
			  {
				  a1->next = new Node(a2->next->data, NULL);
				  a1 = a1->next;
				  a2 = a2->next;
			  }
		  }
		  return list3;
	  }
	  else
	  {
		  List res(list2);
		  return res;
	  }
	  
  }  


 List List::Merge(const List& list2)
  {
	  if (unit != NULL)
	  {
		  if (list2.unit == NULL)
			  return *this;
		  List list3(*this);
		  Node *a1 = list3.unit, *a2 = list2.unit;
		  while (a1->next != NULL)
		  {
			  a1 = a1->next;
		  }
		  a1->next = new Node(list2.unit->data,NULL);
		  a1 = a1->next;
		  a2 = a2->next;
		  while (a2)
		  {
			  a1->next = new Node(a2->data, NULL);
			  a1 = a1->next;
			  a2 = a2->next;
		  }
		  return list3;
	  }
	  else
	  {
		  List res(list2);
		  return res;
	  }
  }


ostream & operator<<(ostream & os, const List & l)
{
	Node *a = l.unit;
	while (a)
	{
		os << a->data << " ";
		a = a->next;
	}
	return os;
}

bool List::operator==(const List & list2) const
{
	int flag = 0;
	Node *a1 = unit;
	Node *a2 = list2.unit;
	while (a1 && a2 && flag)
	{
		if (a1->data != a2->data)
			flag = 1;
		else
		{
			a1 = a1->next;
			a2 = a2->next;
		}

	}
	if (a1 || a2)
		flag = 0;
	if (flag=0)
	return false;
	else return true;
}