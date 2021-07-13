// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dict_Analysis

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "EventLoop.h"
#include "Data.h"
#include "Algorithm.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *Data_Dictionary();
   static void Data_TClassManip(TClass*);
   static void delete_Data(void *p);
   static void deleteArray_Data(void *p);
   static void destruct_Data(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Data*)
   {
      ::Data *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Data));
      static ::ROOT::TGenericClassInfo 
         instance("Data", "Data.h", 9,
                  typeid(::Data), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Data_Dictionary, isa_proxy, 4,
                  sizeof(::Data) );
      instance.SetDelete(&delete_Data);
      instance.SetDeleteArray(&deleteArray_Data);
      instance.SetDestructor(&destruct_Data);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Data*)
   {
      return GenerateInitInstanceLocal((::Data*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Data*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Data_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Data*)0x0)->GetClass();
      Data_TClassManip(theClass);
   return theClass;
   }

   static void Data_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *EventLoop_Dictionary();
   static void EventLoop_TClassManip(TClass*);
   static void *new_EventLoop(void *p = 0);
   static void *newArray_EventLoop(Long_t size, void *p);
   static void delete_EventLoop(void *p);
   static void deleteArray_EventLoop(void *p);
   static void destruct_EventLoop(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventLoop*)
   {
      ::EventLoop *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::EventLoop));
      static ::ROOT::TGenericClassInfo 
         instance("EventLoop", "EventLoop.h", 10,
                  typeid(::EventLoop), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &EventLoop_Dictionary, isa_proxy, 4,
                  sizeof(::EventLoop) );
      instance.SetNew(&new_EventLoop);
      instance.SetNewArray(&newArray_EventLoop);
      instance.SetDelete(&delete_EventLoop);
      instance.SetDeleteArray(&deleteArray_EventLoop);
      instance.SetDestructor(&destruct_EventLoop);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventLoop*)
   {
      return GenerateInitInstanceLocal((::EventLoop*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventLoop*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *EventLoop_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::EventLoop*)0x0)->GetClass();
      EventLoop_TClassManip(theClass);
   return theClass;
   }

   static void EventLoop_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Data(void *p) {
      delete ((::Data*)p);
   }
   static void deleteArray_Data(void *p) {
      delete [] ((::Data*)p);
   }
   static void destruct_Data(void *p) {
      typedef ::Data current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Data

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventLoop(void *p) {
      return  p ? new(p) ::EventLoop : new ::EventLoop;
   }
   static void *newArray_EventLoop(Long_t nElements, void *p) {
      return p ? new(p) ::EventLoop[nElements] : new ::EventLoop[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventLoop(void *p) {
      delete ((::EventLoop*)p);
   }
   static void deleteArray_EventLoop(void *p) {
      delete [] ((::EventLoop*)p);
   }
   static void destruct_EventLoop(void *p) {
      typedef ::EventLoop current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventLoop

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 339,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlETStringgR_Dictionary();
   static void vectorlETStringgR_TClassManip(TClass*);
   static void *new_vectorlETStringgR(void *p = 0);
   static void *newArray_vectorlETStringgR(Long_t size, void *p);
   static void delete_vectorlETStringgR(void *p);
   static void deleteArray_vectorlETStringgR(void *p);
   static void destruct_vectorlETStringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TString>*)
   {
      vector<TString> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TString>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TString>", -2, "vector", 339,
                  typeid(vector<TString>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETStringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TString>) );
      instance.SetNew(&new_vectorlETStringgR);
      instance.SetNewArray(&newArray_vectorlETStringgR);
      instance.SetDelete(&delete_vectorlETStringgR);
      instance.SetDeleteArray(&deleteArray_vectorlETStringgR);
      instance.SetDestructor(&destruct_vectorlETStringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TString> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TString>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETStringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TString>*)0x0)->GetClass();
      vectorlETStringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETStringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETStringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString> : new vector<TString>;
   }
   static void *newArray_vectorlETStringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString>[nElements] : new vector<TString>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETStringgR(void *p) {
      delete ((vector<TString>*)p);
   }
   static void deleteArray_vectorlETStringgR(void *p) {
      delete [] ((vector<TString>*)p);
   }
   static void destruct_vectorlETStringgR(void *p) {
      typedef vector<TString> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TString>

namespace ROOT {
   static TClass *vectorlEAlgorithmmUgR_Dictionary();
   static void vectorlEAlgorithmmUgR_TClassManip(TClass*);
   static void *new_vectorlEAlgorithmmUgR(void *p = 0);
   static void *newArray_vectorlEAlgorithmmUgR(Long_t size, void *p);
   static void delete_vectorlEAlgorithmmUgR(void *p);
   static void deleteArray_vectorlEAlgorithmmUgR(void *p);
   static void destruct_vectorlEAlgorithmmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Algorithm*>*)
   {
      vector<Algorithm*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Algorithm*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Algorithm*>", -2, "vector", 339,
                  typeid(vector<Algorithm*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAlgorithmmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Algorithm*>) );
      instance.SetNew(&new_vectorlEAlgorithmmUgR);
      instance.SetNewArray(&newArray_vectorlEAlgorithmmUgR);
      instance.SetDelete(&delete_vectorlEAlgorithmmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEAlgorithmmUgR);
      instance.SetDestructor(&destruct_vectorlEAlgorithmmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Algorithm*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Algorithm*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAlgorithmmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Algorithm*>*)0x0)->GetClass();
      vectorlEAlgorithmmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAlgorithmmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAlgorithmmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Algorithm*> : new vector<Algorithm*>;
   }
   static void *newArray_vectorlEAlgorithmmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Algorithm*>[nElements] : new vector<Algorithm*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAlgorithmmUgR(void *p) {
      delete ((vector<Algorithm*>*)p);
   }
   static void deleteArray_vectorlEAlgorithmmUgR(void *p) {
      delete [] ((vector<Algorithm*>*)p);
   }
   static void destruct_vectorlEAlgorithmmUgR(void *p) {
      typedef vector<Algorithm*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Algorithm*>

namespace {
  void TriggerDictionaryInitialization_dict_Analysis_Impl() {
    static const char* headers[] = {
"EventLoop.h",
"Data.h",
"Algorithm.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc7_amd64_gcc820/lcg/root/6.14.09/include",
"/afs/cern.ch/work/m/mpresill/HCMN/NewMacros/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "dict_Analysis dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$Data.h")))  __attribute__((annotate("$clingAutoload$EventLoop.h")))  Data;
class __attribute__((annotate("$clingAutoload$EventLoop.h")))  EventLoop;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "dict_Analysis dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "EventLoop.h"
#include "Data.h"
#include "Algorithm.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Data", payloadCode, "@",
"EventLoop", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("dict_Analysis",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_dict_Analysis_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_dict_Analysis_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_dict_Analysis() {
  TriggerDictionaryInitialization_dict_Analysis_Impl();
}
