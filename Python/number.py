import array
import numpy as np
import tuple
def demonstrate_array():
    print("Array Demonstration:")
    # Create an array of integers
    int_array = array.array('i', [1, 2, 3, 4, 5])
    print("Integer Array:", int_array)

    # Append and extend operations
    int_array.append(6)
    int_array.extend([7, 8, 9])
    print("After append and extend:", int_array)

    # Accessing elements
    print("First element:", int_array[0])
    print("Last element:", int_array[-1])

    # Slicing
    print("Sliced array:", int_array[2:5])

    # Array to list conversion
    array_list = int_array.tolist()
    print("Array converted to list:", array_list)
    print()

def demonstrate_numpy():
    print("NumPy Demonstration:")
    # Create a NumPy array
    np_array = np.array([1, 2, 3, 4, 5])
    print("NumPy Array:", np_array)

    # Array operations
    print("Array + 2:", np_array + 2)
    print("Array * 2:", np_array * 2)

    # Create a 2D array
    np_2d_array = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    print("2D Array:\n", np_2d_array)

    # Array shape and dimensions
    print("Shape:", np_2d_array.shape)
    print("Dimensions:", np_2d_array.ndim)

    # Array slicing
    print("First row:", np_2d_array[0])
    print("First column:", np_2d_array[:, 0])

    # Array functions
    print("Sum of all elements:", np.sum(np_2d_array))
    print("Mean of all elements:", np.mean(np_2d_array))
    print()

def demonstrate_tuple():
    print("Tuple Demonstration:")
    # Create a tuple
    my_tuple = (1, "hello", 3.14, [1, 2, 3])
    print("Tuple:", my_tuple)

    # Accessing elements
    print("First element:", my_tuple[0])
    print("Last element:", my_tuple[-1])

    # Tuple unpacking
    a, b, c, d = my_tuple
    print("Unpacked values:", a, b, c, d)

    # Tuple methods
    print("Count of 1:", my_tuple.count(1))
    print("Index of 'hello':", my_tuple.index("hello"))

    # Tuple concatenation
    another_tuple = (5, 6, 7)
    concatenated_tuple = my_tuple + another_tuple
    print("Concatenated tuple:", concatenated_tuple)

    # Nested tuple
    nested_tuple = ((1, 2), (3, 4), (5, 6))
    print("Nested tuple:", nested_tuple)
    print("Element from nested tuple:", nested_tuple[1][0])
    print()

def main():
    print("Array, NumPy, and Tuple Demonstration")
    print("=====================================")
    demonstrate_array()
    demonstrate_numpy()
    demonstrate_tuple()

if __name__ == "__main__":
    main()
