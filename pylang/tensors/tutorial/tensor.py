""" Doc String. """
import os
os.environ['TF_CPP_MIN_LOG_LEVEL']='2'

import tensorflow as tf

def main():
    """ Doc String. """
    node_1 = tf.constant(3.0, tf.float32)
    node_2 = tf.constant(4.0)
    print(node_1, node_2)
    sess = tf.Session()
    print(sess.run([node_1, node_2]))

    node_3 = tf.add(node_1, node_2)
    print("node3: ", node_3)
    print("sess.run(node3): ", sess.run(node_3))

    a = tf.placeholder(tf.float32)
    b = tf.placeholder(tf.float32)
    adder_node = a + b  # + provides a shortcut for tf.add(a, b)    
    print(sess.run(adder_node, {a: 3, b:4.5}))
    print(sess.run(adder_node, {a: [1,3], b: [2, 4]}))    
    
    W = tf.Variable([.3], tf.float32)
    b = tf.Variable([-.3], tf.float32)
    x = tf.placeholder(tf.float32)
    linear_model = W * x + b

    init = tf.global_variables_initializer()
    sess.run(init)
    print(sess.run(linear_model, {x:[1,2,3,4]}))

    y = tf.placeholder(tf.float32)
    squared_deltas = tf.square(linear_model - y)
    loss = tf.reduce_sum(squared_deltas)
    print(sess.run(loss, {x:[1,2,3,4], y:[0,-1,-2,-3]}))

    optimizer = tf.train.GradientDescentOptimizer(0.01)
    train = optimizer.minimize(loss)

    sess.run(init) # reset values to incorrect defaults.
    for i in range(1000):
        print(sess.run([W,b]))
        sess.run(train, {x:[1,2,3,4], y:[0,-1,-2,-3]})

    print(sess.run([W, b]))

if __name__ == "__main__":
    main()
