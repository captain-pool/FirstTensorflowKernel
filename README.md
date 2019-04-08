# My First Tensorflow Kernel
Tensorflow is an open source machine learning Library Developed and Maintained by Google. Tensorflow at it's core uses, C++ to work on every single piece of information it recieves.Tensorflow exposes a C++ API to use it to Develop Stand Alone Shared Libraries such that a developer can Use that and integrate new Operations with Tensorflow Core. This code is either Converted to Python Code, when performing Bazel Build, or it can be loaded as a shared Library into Tensorflow Runtime by calling `tf.load_ops_library(<path_to_shared_library>)`.
Developing Kernels for Tensorflow is Very Important for Contribution to Tensorflow Core, to add Support to Custom Operations as they Grow with time.
Usage:
- Building The Shared Library:
  `$ ./make.sh custom_add.cc`
- Loading into Python Runtime
```python
import tensorflow as tf
custom_module = tf.load_op_library("./custom_add.so")
tensor1 = tf.constant([[0],[1],[2]], dtype = tf.int32)
tensor2 = tf.constant([[1], [2], [3]], dtype = tf.int32)
add_op = custom_module.custom_add(tensor1, tensor2)
print(add_op)
```
