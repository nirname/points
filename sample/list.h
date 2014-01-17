	/*template <typename Type> class List
	{
		private:

			struct Element;

			typedef Element * ElementPointer;
			typedef Type *    TypePointer;

			struct Element
			{
				ElementPointer prev, next;
				TypePointer    object;

				Element(TypePointer _object): next(NULL), prev(NULL), object(_object) {};
			};

			ElementPointer head, tail;

		public:

			List(): head(NULL), tail(NULL) {}
			~List()
			{
				clear();
			}

			void clear()
			{
				while(!is_empty())
				{
					extract_from_head();
				}
			}

			bool is_empty()
			{
				return head == NULL;
			}

			TypePointer first()
			{
				if(is_empty()) {
					return NULL;
				}
				else {
					return head->object;
				}
			};

			TypePointer last()
			{
				if(is_empty()) {
					return NULL;
				}
				else {
					return tail->object;
				}
			};

			void push_in_head(TypePointer _object)
			{
				ElementPointer new_element = new Element(_object);
				if(is_empty())
				{
					head = new_element;
					tail = new_element;
				}
				else
				{
					// link elements
					head->prev = new_element;
					new_element->next = head;
					// move head
					head = new_element;
				}
			}

			void push_in_tail(TypePointer _object)
			{
				ElementPointer new_element = new Element(_object);
				if(is_empty())
				{
					head = new_element;
					tail = new_element;
				}
				else
				{
					// link elements
					tail->next = new_element;
					new_element->prev = tail;
					// move tail
					tail = new_element;
				}
			}

			TypePointer extract_from_head()
			{
				ElementPointer current_element = head;
				if(current_element != NULL)
				{
					TypePointer current_object = current_element->object;
					if(head != tail)
					{
						head = head->next;
						head->prev = NULL;
					}
					else
					{
						head = NULL;
						tail = NULL;
					}
					delete current_element;
					return current_object;
				}
				else
				{
					return NULL;
				}
			}

			TypePointer extract_from_tail()
			{
				ElementPointer current_element = tail;
				if(current_element != NULL)
				{
					TypePointer current_object = current_element->object;
					if(head != tail)
					{
						tail = tail->prev;
						tail->next = NULL;
					}
					else
					{
						head = NULL;
						tail = NULL;
					}
					delete current_element;
					return current_object;
				}
				else
				{
					return NULL;
				}
			}

			void each(void (*action)(TypePointer))
			{
				ElementPointer current_element = head;
				while(current_element != NULL)
				{
					action(current_element->object);
					current_element = current_element->next;
				}
			}

	}; /* List */
