# Fast vector::erase

If you are using vector, Maybe you had experience deleting element of vector.   
This vector::erase delete specific element and reallocate elements after deleted element.   
But This reallocation is sometimes too slow. (when element's move semantic is defined not well).   

So my vector::erase_move_lastelement function just delete target element and reallocate only vector's last element to deleted element's pos.   
Sometimes this will reduce overhead dramatically.   

## This is how vector::erase works.

1  2  3  4  5   

1  X  3  4  5 ( X is deleted element )   

1  **3  4  5** ( element '3', '4', '5' is reallocated )   

## How my library's vector::erase_move_lastelement works

1  2  3  4  5   

1  X  3  4  5 ( X is deleted element )   

1  **5**  3  4  ( only element '5' is reallocated )   

