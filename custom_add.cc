#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/shape_inference.h"
#include "tensorflow/core/framework/op_kernel.h"
using namespace tensorflow;
REGISTER_OP("CustomAdd")
  .Attr("T: {int32, float32, int64} = DT_INT32")
  .Input("tensor1: T")
  .Input("tensor2: T")
  .Output("output_: T")
  .SetShapeFn([](::tensorflow::shape_inference::InferenceContext *ctx){
  ctx->set_output(0, ctx->input(0));
  return Status::OK();
  });


template<typename T>
class CustomAddOp: public OpKernel{
public:
explicit CustomAddOp(OpKernelConstruction *ctx):OpKernel(ctx){}
void Compute(OpKernelContext *ctx) override{
    const Tensor& input_tensor_1 = ctx->input(0);
    const Tensor& input_tensor_2 = ctx->input(1);
    Tensor *output_tensor = NULL;
    OP_REQUIRES_OK(ctx, ctx->allocate_output(0, input_tensor_1.shape(), &output_tensor));
    OP_REQUIRES(ctx, input_tensor_1.NumElements() == input_tensor_2.NumElements(), errors::InvalidArgument("The Number of Elements Doesn't Match!"));
    auto input_tensor_flat_1 = input_tensor_1.flat<T>();
    auto input_tensor_flat_2 = input_tensor_2.flat<T>();
    auto output_tensor_flat = output_tensor->template flat<T>();
    const int N = input_tensor_flat_1.size();
    for(int i = 0;i < N; i++){
      output_tensor_flat(i) = input_tensor_flat_1(i) + input_tensor_flat_2(i);
    }

  }
};

REGISTER_KERNEL_BUILDER(
Name("CustomAdd")
.Device(DEVICE_CPU)
.TypeConstraint<int32>("T"),
CustomAddOp<int32>);
REGISTER_KERNEL_BUILDER(
Name("CustomAdd")
.Device(DEVICE_CPU)
.TypeConstraint<double>("T"),
CustomAddOp<double>);
REGISTER_KERNEL_BUILDER(
Name("CustomAdd")
.Device(DEVICE_CPU)
.TypeConstraint<float>("T"),
CustomAddOp<float>);
