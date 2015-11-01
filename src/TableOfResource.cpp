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

void Resource::print() {
    std::string res_s;
    switch (res) {
        case R_VAR: res_s = "R_VAR"; break;
        case R_CONST: res_s = "R_CONST"; break;
        case R_LABEL: res_s = "R_LABEL"; break;
        case R_FUNC: res_s = "R_FUNC"; break;
    }
    std::string val_s;
    switch (type) {
        case V_INTEGER: val_s = "V_INTEGER"; break;
        case V_REAL: val_s = "V_REAL"; break;
        case V_BOOLEAN: val_s = "V_BOOLEAN"; break;
        case V_STRING: val_s = "V_STRING"; break;
        case V_NULL: val_s = "V_NULL"; break;
    }
    printf("%16s\t%16s\t%16s\t%16s", res_s.c_str(), name.c_str(), val_s.c_str(), value.c_str());
}

Resource::Resource(std::string name, resource_t res, value_t type, std::string value) {
    this->name = name;
    this->res = res;
    this->type = type;
    this->value = value;
}

//---------------------------------------------------------------
class TableOfResource {
public:
    TableOfResource();
    TableOfResource(std::string name);
    
    // Name of block
    std::string name;
    
    // Map for resource in blok
    std::map<std::string, Resource> table;
    // TODO: что-то для перегрузки операторов

    void print();
};

TableOfResource::TableOfResource() {
    this->name = "";
}

TableOfResource::TableOfResource(std::string name) {
    this->name = name;
}

void TableOfResource::print() {
    std::map<std::string, Resource>::iterator it = table.begin();
    printf("%16s\t%16s\t%16s\t%16s\n", "Resource type", "Name", "Value type", "Value");
    for (; it != table.end(); ++it) {
        it->second.print();
        std::cout << std::endl;
    }
}
