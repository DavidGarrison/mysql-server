/*
 Copyright (c) 2014, Oracle and/or its affiliates. All rights
 reserved.
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; version 2 of
 the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 02110-1301  USA
*/

#include <NdbApi.hpp>

#include "adapter_global.h"
#include "js_wrapper_macros.h"
#include "DBTransactionContext.h"
#include "NativeMethodCall.h"
#include "NdbWrapperErrors.h"

using namespace v8;

Handle<Value> tryImmediateStartTransaction(const Arguments &);
Handle<Value> prepareAndExecuteScan(const Arguments &);
Handle<Value> execute(const Arguments &);
Handle<Value> executeAsynch(const Arguments &);
Handle<Value> getPendingOperations(const Arguments &);

class DBTransactionContextEnvelopeClass : public Envelope {
public:
  DBTransactionContextEnvelopeClass() : Envelope("DBTransactionContext") {
    DEFINE_JS_FUNCTION(Envelope::stencil, 
      "tryImmediateStartTransaction", tryImmediateStartTransaction);
    DEFINE_JS_FUNCTION(Envelope::stencil, 
      "prepareAndExecuteScan", prepareAndExecuteScan);
    DEFINE_JS_FUNCTION(Envelope::stencil, "execute", execute);
    DEFINE_JS_FUNCTION(Envelope::stencil, "executeAsynch", executeAsynch);
    DEFINE_JS_FUNCTION(Envelope::stencil, 
      "getPendingOperations", getPendingOperations);    
  }
};

DBTransactionContextEnvelopeClass DBTransactionContextEnvelope;

void setJsWrapper(DBTransactionContext *ctx) {
  HandleScope scope;
  Local<Object> localObj = DBTransactionContextEnvelope.newWrapper();
  wrapPointerInObject(ctx, DBTransactionContextEnvelope, localObj);
  ctx->jsWrapper = Persistent<Value>::New(localObj);
}

Handle<Value> tryImmediateStartTransaction(const Arguments &args) {
  HandleScope scope;
  DBTransactionContext * ctx = unwrapPointer<DBTransactionContext *>(args.Holder());
  bool r = ctx->tryImmediateStartTransaction();
  return r ? True() : False();
}

Handle<Value> prepareAndExecuteScan(const Arguments &args) {
  DEBUG_MARKER(UDEB_DEBUG);
  REQUIRE_ARGS_LENGTH(1);
  typedef NativeMethodCall_0_<NdbScanOperation *, DBTransactionContext> MCALL;
  MCALL * mcallptr = new MCALL(& DBTransactionContext::prepareAndExecuteScan, args);
  mcallptr->wrapReturnValueAs(getNdbScanOperationEnvelope());
  mcallptr->errorHandler = getNdbErrorIfNull<NdbScanOperation *, DBTransactionContext>;
  mcallptr->runAsync();
  
  return Undefined();
}

