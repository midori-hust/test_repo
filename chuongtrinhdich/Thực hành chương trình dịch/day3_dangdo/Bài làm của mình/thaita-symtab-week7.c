/* Tran Anh Thai
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);
SymTab* symtab;
Type* intType;
Type* charType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
  // TODO
  Type* tmp=(Type*)malloc(sizeof(Type));
  tmp->typeClass=type->typeClass;
  if(tmp->typeClass == TP_ARRAY)
    {
      tmp->arraySize=type->arraySize;
      tmp->elementType=duplicateType(type->elementType);
    }
  return tmp;
}

int compareType(Type* type1, Type* type2) {
  // TODO
  if(type1->typeClass==type2->typeClass)
    {
      if(type1->typeClass==TP_ARRAY)
	{
	  if(type1->arraySize==type2->arraySize)
	    return compareType(type1->elementType,type2->elementType);
	  else return 0;
	}
      else return 1;
    }
  else return 1;
}

void freeType(Type* type) {
  // TODO
  if(type->typeClass == TP_INT || type->typeClass == TP_CHAR)
    free(type);
  else if(type->typeClass == TP_ARRAY)
    {
      freeType(type->elementType);
      freeType(type);
    }
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  // TODO
  ConstantValue* value=(ConstantValue*)malloc(sizeof(ConstantValue));
  value->type=TP_INT;
  value->intValue=i;
  return value;
}

ConstantValue* makeCharConstant(char ch) {
  // TODO
  ConstantValue* value=(ConstantValue*)malloc(sizeof(ConstantValue));
  value->type=TP_CHAR;
  value->intValue=ch;
  return value;

}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO
  ConstantValue *tmp=(ConstantValue*)malloc(sizeof(ConstantValue));
  tmp->type=v->type;
  if(tmp->type==TP_INT)
    tmp->intValue=v->intValue;
  else 
    tmp->charValue=v->charValue;
  return tmp;
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  // TODO
  Object *tmp=(Object*)malloc(sizeof(Object));
  strcpy(tmp->name,name);
  tmp->kind=OBJ_CONSTANT;
  tmp->constAttrs=(ConstantAttributes*)malloc(sizeof(ConstantAttributes));
  return tmp;
}

Object* createTypeObject(char *name) {
  // TODO
  Object* tmp=(Object*)malloc(sizeof(Object));
  strcpy(tmp->name,name);
  tmp->kind=OBJ_TYPE;
  tmp->typeAttrs=(TypeAttributes*)malloc(sizeof(TypeAttributes));
  return tmp;
}

Object* createVariableObject(char *name) {
  // TODO
  Object* tmp=(Object*)malloc(sizeof(Object));
  strcpy(tmp->name,name);
  tmp->kind=OBJ_VARIABLE;
  tmp->varAttrs=(VariableAttributes*)malloc(sizeof(VariableAttributes));
  tmp->varAttrs->scope=symtab->currentScope;
  return tmp;
}

Object* createFunctionObject(char *name) {
  // TODO
  Object* tmp=(Object*)malloc(sizeof(Object));
  strcpy(tmp->name,name);
  tmp->kind=OBJ_FUNCTION;
  tmp->funcAttrs=(FunctionAttributes*)malloc(sizeof(FunctionAttributes));
  tmp->funcAttrs->paramList=NULL;
  tmp->funcAttrs->scope=createScope(tmp,symtab->currentScope);
  return tmp;
}

Object* createProcedureObject(char *name) {
  // TODO
  Object* tmp=(Object*)malloc(sizeof(Object));
  strcpy(tmp->name,name);
  tmp->kind=OBJ_PROCEDURE;
  tmp->procAttrs=(ProcedureAttributes*)malloc(sizeof(ProcedureAttributes));
  tmp->procAttrs->paramList=NULL;
  tmp->procAttrs->scope=createScope(tmp,symtab->currentScope);
  return tmp;
}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO
  Object*tmp=(Object*)malloc(sizeof(Object));
  strcpy(tmp->name,name);
  tmp->kind=OBJ_PARAMETER;
  tmp->paramAttrs=(ParameterAttributes*)malloc(sizeof(ParameterAttributes));
  tmp->paramAttrs->function=owner;
  tmp->paramAttrs->kind=kind;
  return tmp;

}

void freeObject(Object* obj) {
  // TODO
  if(obj->kind == OBJ_CONSTANT)
    {
      free(obj->constAttrs->value);
      free(obj->constAttrs);
    }
  else if(obj->kind==OBJ_TYPE)
    {
      free(obj->typeAttrs->actualType);
      free(obj->typeAttrs);
    }
  else if(obj->kind==OBJ_FUNCTION)
    {
      freeReferenceList(obj->funcAttrs->paramList);
      freeScope(obj->funcAttrs->scope);
      freeType(obj->funcAttrs->returnType);
      free(obj->funcAttrs);
    }
  else if(obj->kind==OBJ_PROCEDURE)
    {
      freeReferenceList(obj->procAttrs->paramList);
      freeScope(obj->procAttrs->scope);
      free(obj->procAttrs);
    }
  else if(obj->kind==OBJ_PROGRAM)
    {
      freeScope(obj->progAttrs->scope);
      free(obj->progAttrs);
    }
  else if(obj->kind==OBJ_PARAMETER)
    {
      freeType(obj->paramAttrs->type);
      free(obj->paramAttrs);
    }
  else if(obj->kind==OBJ_VARIABLE)
    {
      free(obj->varAttrs->type);
      free(obj->varAttrs);
    }
  free(obj);
}

void freeScope(Scope* scope) {
  // TODO
  freeObjectList(scope->objList);
  free(scope);
}

void freeObjectList(ObjectNode *objList) {
  // TODO
  ObjectNode* tmp=objList;
  ObjectNode* tmp1;
  while(tmp!=NULL)
    {
      tmp1=tmp;
      tmp=tmp->next;
      freeObject(tmp1->object);
      free(tmp1);
    }
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
  ObjectNode* tmp= objList;
  ObjectNode* tmp1;
  while(tmp!=NULL)
    {
      tmp1=tmp;
      tmp=tmp->next;
      free(tmp1);
    }
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  // TODO
  while(objList!=NULL)
    {
      if(strcmp(objList->object->name,name)==0)
	return objList->object;
      else objList=objList->next;
    }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


