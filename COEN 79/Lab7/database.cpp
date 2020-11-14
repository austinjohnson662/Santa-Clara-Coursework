// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    //assigns appropriate values to aloc_slots and used_slots. Assigns company array.
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
        aloc_slots = src.aloc_slots;
        used_slots = src.used_slots;
        company_array = new company[aloc_slots];
        *company_array = *src.company_array;
    }
    
    //delete the existing array. create a new array and copies the values of the companies using std::copy.
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
        if (this == &rhs)
            return *this;
        delete[] company_array;
        company_array = new company[rhs.aloc_slots];
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array);
        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;
        return *this;
    }
    
    //deletes the company_array and sets the aloc_slots and used_slots to 0.
    database::~database() {
        delete[] company_array;
        used_slots = 0;
        aloc_slots = 0;
    }
    
    //creates a new array of the size new_capacity. Uses std::copy to copy the values into the new array. Assign company_array with the new array.
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        company* temp = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, temp);
        if (company_array != NULL) {
            delete[] company_array;
        }
        aloc_slots = new_capacity;
        company_array = temp;
    }
    
    //Checks if more slots and are needed and adds them if appropriate. inserts the company to the end of the array.
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
        if (used_slots == aloc_slots)
            reserve(aloc_slots + 1);
        company temp = company(entry);
        company_array[used_slots++] = temp;
        return true;
    }
    
    //if the item is not found the function does nothing and returns false. If it is in the array then it inserts the new product in its product list.
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);
        
        size_type index = search_company(company);
        if (index != COMPANY_NOT_FOUND) {
            company_array[index].insert(product_name, price);
            return true;
        }
        return false;
    }
    
    //overwrites the company's slot in the array by shifting the array to the right of the company to the left one slot.
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);

        if (company_index == COMPANY_NOT_FOUND)
            return false;
        int i;
        for (i = company_index; i < used_slots - 1; i++) {
            company_array[i] = company_array[i + 1];
        }
        used_slots--;
        return true;
    }
    
    //searches for the company. If not found return false. If found use the erase function and return its return value.
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        size_type company_index = search_company(cName);
        if (company_index == COMPANY_NOT_FOUND)
            return false;
        return company_array[company_index].erase(pName);
    }
    
    
    //loops the through the array and if they are equivalent return the index. If not return the constant COMPANY_NOT_FOUND
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
        size_type i;
        for (i = 0; i < used_slots; i++) {
            if (company_array[i].get_name() == company)
                return i;
        }
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
