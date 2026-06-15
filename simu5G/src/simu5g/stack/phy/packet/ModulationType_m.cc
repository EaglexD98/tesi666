//
// Generated file, do not edit! Created by opp_msgtool 6.2 from simu5g/stack/phy/packet/ModulationType.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "ModulationType_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace simu5g {

Register_Enum(simu5g::ModulationClass, (simu5g::ModulationClass::MOD_CLASS_UNKNOWN, simu5g::ModulationClass::MOD_CLASS_IR, simu5g::ModulationClass::MOD_CLASS_FHSS, simu5g::ModulationClass::MOD_CLASS_DSSS, simu5g::ModulationClass::MOD_CLASS_ERP_PBCC, simu5g::ModulationClass::MOD_CLASS_DSSS_OFDM, simu5g::ModulationClass::MOD_CLASS_ERP_OFDM, simu5g::ModulationClass::MOD_CLASS_OFDM, simu5g::ModulationClass::MOD_CLASS_HT));

Register_Enum(simu5g::CodeRate, (simu5g::CodeRate::CODE_RATE_UNDEFINED, simu5g::CodeRate::CODE_RATE_3_4, simu5g::CodeRate::CODE_RATE_2_3, simu5g::CodeRate::CODE_RATE_1_2, simu5g::CodeRate::CODE_RATE_5_6));

ModulationType::ModulationType()
{
}

ModulationType::ModulationType(const ModulationType& other)
{
    copy(other);
}

ModulationType::~ModulationType()
{
}

ModulationType& ModulationType::operator=(const ModulationType& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void ModulationType::copy(const ModulationType& other)
{
    this->isMandatory = other.isMandatory;
    this->bandwidth = other.bandwidth;
    this->dataRate = other.dataRate;
    this->codeRate = other.codeRate;
    this->phyRate = other.phyRate;
    this->constellationSize = other.constellationSize;
    this->modulationClass = other.modulationClass;
    this->frequency = other.frequency;
}

void ModulationType::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->isMandatory);
    doParsimPacking(b,this->bandwidth);
    doParsimPacking(b,this->dataRate);
    doParsimPacking(b,this->codeRate);
    doParsimPacking(b,this->phyRate);
    doParsimPacking(b,this->constellationSize);
    doParsimPacking(b,this->modulationClass);
    doParsimPacking(b,this->frequency);
}

void ModulationType::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->isMandatory);
    doParsimUnpacking(b,this->bandwidth);
    doParsimUnpacking(b,this->dataRate);
    doParsimUnpacking(b,this->codeRate);
    doParsimUnpacking(b,this->phyRate);
    doParsimUnpacking(b,this->constellationSize);
    doParsimUnpacking(b,this->modulationClass);
    doParsimUnpacking(b,this->frequency);
}

bool ModulationType::getIsMandatory() const
{
    return this->isMandatory;
}

void ModulationType::setIsMandatory(bool isMandatory)
{
    this->isMandatory = isMandatory;
}

uint32_t ModulationType::getBandwidth() const
{
    return this->bandwidth;
}

void ModulationType::setBandwidth(uint32_t bandwidth)
{
    this->bandwidth = bandwidth;
}

uint32_t ModulationType::getDataRate() const
{
    return this->dataRate;
}

void ModulationType::setDataRate(uint32_t dataRate)
{
    this->dataRate = dataRate;
}

CodeRate ModulationType::getCodeRate() const
{
    return this->codeRate;
}

void ModulationType::setCodeRate(CodeRate codeRate)
{
// cplusplus {{
    switch (codeRate) {
        case CODE_RATE_5_6:
            phyRate = dataRate * 6 / 5;
            break;
        case CODE_RATE_3_4:
            phyRate = dataRate * 4 / 3;
            break;
        case CODE_RATE_2_3:
            phyRate = dataRate * 3 / 2;
            break;
        case CODE_RATE_1_2:
            phyRate = dataRate * 2 / 1;
            break;
        case CODE_RATE_UNDEFINED:
        default:
            phyRate = dataRate;
            break;
    }
// }}
    this->codeRate = codeRate;
}

uint32_t ModulationType::getPhyRate() const
{
    return this->phyRate;
}

void ModulationType::setPhyRate(uint32_t phyRate)
{
    this->phyRate = phyRate;
}

uint8_t ModulationType::getConstellationSize() const
{
    return this->constellationSize;
}

void ModulationType::setConstellationSize(uint8_t constellationSize)
{
    this->constellationSize = constellationSize;
}

ModulationClass ModulationType::getModulationClass() const
{
    return this->modulationClass;
}

void ModulationType::setModulationClass(ModulationClass modulationClass)
{
    this->modulationClass = modulationClass;
}

uint32_t ModulationType::getFrequency() const
{
    return this->frequency;
}

void ModulationType::setFrequency(uint32_t frequency)
{
    this->frequency = frequency;
}

class ModulationTypeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_isMandatory,
        FIELD_bandwidth,
        FIELD_dataRate,
        FIELD_codeRate,
        FIELD_phyRate,
        FIELD_constellationSize,
        FIELD_modulationClass,
        FIELD_frequency,
    };
  public:
    ModulationTypeDescriptor();
    virtual ~ModulationTypeDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ModulationTypeDescriptor)

ModulationTypeDescriptor::ModulationTypeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(simu5g::ModulationType)), "")
{
    propertyNames = nullptr;
}

ModulationTypeDescriptor::~ModulationTypeDescriptor()
{
    delete[] propertyNames;
}

bool ModulationTypeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ModulationType *>(obj)!=nullptr;
}

const char **ModulationTypeDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ModulationTypeDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ModulationTypeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int ModulationTypeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_isMandatory
        FD_ISEDITABLE,    // FIELD_bandwidth
        FD_ISEDITABLE,    // FIELD_dataRate
        0,    // FIELD_codeRate
        FD_ISEDITABLE,    // FIELD_phyRate
        FD_ISEDITABLE,    // FIELD_constellationSize
        0,    // FIELD_modulationClass
        FD_ISEDITABLE,    // FIELD_frequency
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *ModulationTypeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "isMandatory",
        "bandwidth",
        "dataRate",
        "codeRate",
        "phyRate",
        "constellationSize",
        "modulationClass",
        "frequency",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int ModulationTypeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "isMandatory") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "dataRate") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "codeRate") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "phyRate") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "constellationSize") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "modulationClass") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "frequency") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *ModulationTypeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_isMandatory
        "uint32_t",    // FIELD_bandwidth
        "uint32_t",    // FIELD_dataRate
        "simu5g::CodeRate",    // FIELD_codeRate
        "uint32_t",    // FIELD_phyRate
        "uint8_t",    // FIELD_constellationSize
        "simu5g::ModulationClass",    // FIELD_modulationClass
        "uint32_t",    // FIELD_frequency
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **ModulationTypeDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_isMandatory: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        case FIELD_codeRate: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_modulationClass: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *ModulationTypeDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_isMandatory:
            if (!strcmp(propertyName, "getter")) return "getIsMandatory";
            return nullptr;
        case FIELD_codeRate:
            if (!strcmp(propertyName, "enum")) return "simu5g::CodeRate";
            return nullptr;
        case FIELD_modulationClass:
            if (!strcmp(propertyName, "enum")) return "simu5g::ModulationClass";
            return nullptr;
        default: return nullptr;
    }
}

int ModulationTypeDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ModulationTypeDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ModulationType'", field);
    }
}

const char *ModulationTypeDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ModulationTypeDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        case FIELD_isMandatory: return bool2string(pp->getIsMandatory());
        case FIELD_bandwidth: return ulong2string(pp->getBandwidth());
        case FIELD_dataRate: return ulong2string(pp->getDataRate());
        case FIELD_codeRate: return enum2string(pp->getCodeRate(), "simu5g::CodeRate");
        case FIELD_phyRate: return ulong2string(pp->getPhyRate());
        case FIELD_constellationSize: return ulong2string(pp->getConstellationSize());
        case FIELD_modulationClass: return enum2string(pp->getModulationClass(), "simu5g::ModulationClass");
        case FIELD_frequency: return ulong2string(pp->getFrequency());
        default: return "";
    }
}

void ModulationTypeDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        case FIELD_isMandatory: pp->setIsMandatory(string2bool(value)); break;
        case FIELD_bandwidth: pp->setBandwidth(string2ulong(value)); break;
        case FIELD_dataRate: pp->setDataRate(string2ulong(value)); break;
        case FIELD_phyRate: pp->setPhyRate(string2ulong(value)); break;
        case FIELD_constellationSize: pp->setConstellationSize(string2ulong(value)); break;
        case FIELD_frequency: pp->setFrequency(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ModulationType'", field);
    }
}

omnetpp::cValue ModulationTypeDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        case FIELD_isMandatory: return pp->getIsMandatory();
        case FIELD_bandwidth: return (omnetpp::intval_t)(pp->getBandwidth());
        case FIELD_dataRate: return (omnetpp::intval_t)(pp->getDataRate());
        case FIELD_codeRate: return static_cast<int>(pp->getCodeRate());
        case FIELD_phyRate: return (omnetpp::intval_t)(pp->getPhyRate());
        case FIELD_constellationSize: return (omnetpp::intval_t)(pp->getConstellationSize());
        case FIELD_modulationClass: return static_cast<int>(pp->getModulationClass());
        case FIELD_frequency: return (omnetpp::intval_t)(pp->getFrequency());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ModulationType' as cValue -- field index out of range?", field);
    }
}

void ModulationTypeDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        case FIELD_isMandatory: pp->setIsMandatory(value.boolValue()); break;
        case FIELD_bandwidth: pp->setBandwidth(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_dataRate: pp->setDataRate(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_phyRate: pp->setPhyRate(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_constellationSize: pp->setConstellationSize(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_frequency: pp->setFrequency(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ModulationType'", field);
    }
}

const char *ModulationTypeDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ModulationTypeDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ModulationTypeDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ModulationType *pp = omnetpp::fromAnyPtr<ModulationType>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ModulationType'", field);
    }
}

}  // namespace simu5g

namespace omnetpp {

}  // namespace omnetpp

