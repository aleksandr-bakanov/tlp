//---------------------------------------------------------------
// Type of resources
typedef enum {
    R_VAR,
    R_CONST,
    R_LABEL,
    R_FUNC
} resource_t;

//---------------------------------------------------------------
// Type of value
typedef enum {
    V_INTEGER,
    V_REAL,
    V_BOOLEAN,
    V_STRING,
    V_NULL
} value_t;

//---------------------------------------------------------------
// Class for resources
class Resource {
public:
    Resource(std::string name, resource_t res, value_t type, std::string value);
    
    // Name of resource
    std::string name;
    // Type of resource
    resource_t res;
    // Type of value
    value_t type;
    // Value
    std::string value;
    
    void print();
};

Resource::Resource(std::string name, resource_t res, value_t type, std::string value) {
    this->name = name;
    this->res = res;
    this->type = type;
    this->value = value;
}

void Resource::print() {
    std::cout << this->name << " " << this->value << std::endl;
}

//---------------------------------------------------------------
class TableOfResource {
public:
    TableOfResource(std::string name, int priority);
    
    // Name of block
    std::string name;
    // Priority (highest == 0)
    int priority;
    
    // Map for resource in blok
    std::map<std::string, Resource> table;
    // TODO: что-то для перегрузки операторов
    
    
    void print();
};

TableOfResource::TableOfResource(std::string name, int priority) {
    this->name = name;
    this->priority = priority;
}

void TableOfResource::print() {
    std::map<std::string, Resource>::iterator it = table.begin();
    for (; it != table.end(); ++it) {
        std::cout << it->first << " => ";
        it->second.print();
        std::cout << std::endl;
    }
}
