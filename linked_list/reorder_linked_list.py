
class Solution:
    def get_len(self, current_pointer):
        if isinstance(current_pointer.next, type(None)):
            return 1
        
        return 1 + self.get_len(current_pointer.next)
    
    def break_into_two(self, head, num_first_half):
        counter = 0
        head_node_1 = head
        current_node = head_node_1
        
        for i in range(num_first_half - 1):
            current_node = current_node.next
        
        
        head_node_2 = current_node.next
        current_node.next = None
        
        return head_node_1, head_node_2
    
    def reverse_list(self, head):
        pointer_1 = None
        pointer_2 = head
        if isinstance(pointer_2, type(None)):
            return pointer_2
        
        pointer_3 = head.next
        
        
        '''
        we just have 1 node
        '''
        if isinstance(pointer_3, type(None)):
            return head
        
        while(not isinstance(pointer_3, type(None))):
            pointer_2.next = pointer_1
            pointer_1 = pointer_2
            pointer_2 = pointer_3
            pointer_3 = pointer_3.next

        
        pointer_2.next = pointer_1
        return pointer_2
    
    def print_list(self, head):
        current_pointer = head
        a_str = "["
        while(not isinstance(current_pointer, type(None))):
            a_str = a_str + str(current_pointer.val) + ","
            current_pointer = current_pointer.next
        a_str = a_str[:-1] + "]"
        print(a_str)

    
    def merge_two_lists(self, head, reversed_head):
        
        pointer_back_head = head
        pointer_front_head = head.next
        pointer_rev_first = reversed_head
        while(not isinstance(pointer_rev_first, type(None))):
            pointer_rev_prev = pointer_rev_first
            pointer_rev_first = pointer_rev_first.next
            pointer_rev_prev.next = None
            temp_node = pointer_rev_prev
            temp_node.next = pointer_front_head
            pointer_back_head.next = temp_node
            pointer_back_head = pointer_front_head
            pointer_front_head = pointer_front_head.next
        
                    
            
            
        return head
    
    def reorderList(self, head: Optional[ListNode]) -> None:
        """
        Do not return anything, modify head in-place instead.
        """

        input_len = self.get_len(head)
        if input_len != 1:
        
            first_half = input_len//2 + 1
            head_node_1, head_node_2 = self.break_into_two(head, first_half)

            head_node_2 = self.reverse_list(head_node_2)

            head = self.merge_two_lists(head_node_1, head_node_2)
       
        
        