TF_CFLAGS=$(python3 -c "import tensorflow as tf;print(' '.join(tf.sysconfig.get_compile_flags()))")
TF_LFLAGS=$(python3 -c "import tensorflow as tf;print(' '.join(tf.sysconfig.get_link_flags()))")
SHARED_NAME=$(echo $1 | cut -f1 -d.).so
g++ -std=c++11 -shared $1 -o $SHARED_NAME -fPIC $TF_CFLAGS $TF_LFLAGS
