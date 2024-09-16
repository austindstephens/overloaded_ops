#include <iostream>

using namespace std;

class A {
	private:
		int* data;
		int size;

		int other;

	public:
		// Default constructor
		A() {
			int i;

			other = 100;

			size = 5;
			data = new int[size];
			
			for(i = 0; i < size; ++i)
				data[i] = 20;
		}

		// Destructor
		~A() {
			delete [] data;
			data = nullptr;
		}

		// Copy constructor, called on object being created/copied
		A(const A& obj) {
			int i;

			// Set the size equal
			this->size = obj.size;
			this->data = new int[this->size];

			for(i = 0; i < this->size; ++i)
				this->data[i] = obj.data[i];

			cout << "Copy constructor called!\n";
		}

		 /* if we just returned void, which we could, then
		 * expressions like a = b = c; would not be allowed,
		 * because in a = b.operator=(c);, the right returns
		 * void! both parameter object and function itself
		 * is const because we don't modify either operand
		 * objects */
		 A& operator=(const A& obj) {
			 int i;

			 // Check for self-assignment
			 if(this == &obj) {
				 exit(1);
			 }

			 // Assign the other member
			 this->other = obj.other;

			 /* Assign the array values; check if left object
			  * has already been constructed; if array size
			  * is not equal, we want it to be, so we deallocate
			  * memory and allocate the appropriate number of
			  * bytes so that we can assign right to left */
			 if(this->size > 0) {
				 
				 // Set the size equal
				 this->size = obj.size;
				 
				 // deallocate the existing memory
				 delete [] this->data;
				 // allocate new memory for array
				 this->data = new int[this->size];
				 
				 for(i = 0; i < this->size; ++i) {
					 this->data[i] = obj.data[i];
				 }
			 }

			 cout << "Assignment op called!\n";

			 // Return by reference so copy constructor not called
			 return *this;
		 }

		/* RBV allows cascading */
		A operator+(const A&) const;

};

// We return the temp object we create here; NO RBR
A A::operator+(const A& obj) const {
	A temp;
	temp.other = this->other + obj.other;

	cout << "+ operator called!\n";

	/* we'll need an assignment operator to perform assign ojects,
	 * which we have defined previously; we couldn't return by
	 * reference an auto local variable of this function */
	return temp;
}

int main(int argc, char* argv[]) {
	A a1;

	// Copy constructor
	A a2 = a1;

	// a3 has been constructed
	A a3;

	// Call assignment operator
	a3 = a1;

	// a3 = a2 + a1;
}
