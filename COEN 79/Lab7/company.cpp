// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //creates a new company with the parameter as the name
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //assigns the company name then uses list_copy from node to copy the list
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        this->company_name = src.company_name;
        list_copy(src.head_ptr, this->head_ptr, this->tail_ptr);
    }

    //assigns the company name then uses list_copy from node to copy the list
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        this->company_name = src.company_name;
        list_copy(src.get_head(), head_ptr, tail_ptr);
        return *this;
    }
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    //use the list functions to insert items in the two cases of empty list and non empty list
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            list_init(this->head_ptr, this->tail_ptr, product_name, price);
        }
        else {
            list_tail_insert(this->tail_ptr, product_name, price);
        }
        
        return true;
    }

    //loops through the array until the name is found. Once found the links are reassigned to relink the list.
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        if (!list_contains_item(this->head_ptr, product_name))
            return false;
        node* precursor = this->head_ptr, *cursor = NULL;
        while (precursor->getLink()->getName() != product_name)
            precursor = precursor->getLink();
        cursor = precursor->getLink();
        precursor->setLink(cursor->getLink());
        delete cursor;
        return true;
    }
    
    
}
