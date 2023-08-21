import random
def double_and_add(point, scalar):
    # Initialize result as the identity element
    result = 0

    # Convert the scalar to binary
    binary_scalar = bin(scalar)[2:]

    # Perform double-and-add algorithm
    for bit in binary_scalar:
        result = result*2
        if bit == '1':
            result += point
    return result


def error_detection(scalar_bits,width):
    window = ""
    counter = 0
    pre_pattern_counter = {}
    for bit in scalar_bits:
        window += bit
        counter += 1
        if(counter < len(scalar_bits)):
            if len(window) == width or counter == len(scalar_bits):
                # Process the window when it reaches 5 bits or when it's the last bit
                window_value = int(window, 2)
                try:
                    pre_pattern_counter[window_value]+=1
                except Exception as e:
                    pre_pattern_counter[window_value] = 1
                window = "" 
    return pre_pattern_counter
    
def window_method(point, scalar,width):
    post_pattern_counter = {}
    precomputed_points = []
    current_point = point
    for _ in range(2 ** width):
        precomputed_points.append(current_point)
        current_point = point + current_point  # Point addition operation
    scalar_bits = bin(scalar)[2:]
    print(scalar_bits)
    result = 0  # Initial result is the point at infinity
    window = ""
    pre_pattern_counter = error_detection(scalar_bits,width)
    print(pre_pattern_counter)
    counter = 0
    for bit in scalar_bits: # Covered
        counter += 1 # Covered.
        window += bit # Covered
        if len(window) == width or counter == len(scalar_bits): # Covered
            window_value = int(window, 2) # Covered
            # print(window_value)
            #Shifting
            for _ in range(len(window)): # Not Covered
                result = result + result # Not Covered
                # print(result)
            try:
                post_pattern_counter[window_value]+=1
            except Exception as e:
                post_pattern_counter[window_value] = 1
            if window_value != 0:
                result = result + precomputed_points[window_value - 1]  #Not covered
                print(result)
            window = ""
    return result

def fault_calcuation(scalar_bits,width,error_number):
    len_scalar_bits = len(scalar_bits)
    A = len_scalar_bits
    W = width
    faulty_PC = []
    possible_fault_domain = (5*A)+(int((2*A)/W))
    for _ in range(error_number):
        faulty_PC.append(random.randint(1,possible_fault_domain))
    return faulty_PC

def fault_possibility(PC,faulty_PC,line_number,err_number):
    if(PC in faulty_PC):
        err_number = err_number + 1
        # print(line_number)
        return err_number,True
    else:
        return err_number,False

    #3A + 3A/W



def faulty_window_method(point, scalar,width,number_of_faults):
    global detected_error
    global err_number
    PC = 0
    err_number = 0
    post_pattern_counter = {}
    precomputed_points = []
    current_point = point
    for _ in range(2 ** width):
        precomputed_points.append(current_point)
        current_point = point + current_point  # Point addition operation
    scalar_bits = bin(scalar)[2:]
    # print(scalar_bits)
    result = 0  # Initial result is the point at infinity
    window = ""
    pre_pattern_counter = error_detection(scalar_bits,width)
    # print(pre_pattern_counter)
    faulty_PC = fault_calcuation(scalar_bits,width,number_of_faults)
    counter = 0
    for bit in scalar_bits: # Covered
        PC += 1
        err_number,_ = fault_possibility(PC,faulty_PC,105,err_number) #A
        if(_):
            break
        counter += 1 # Covered
        PC += 1
        err_number,_ = fault_possibility(PC,faulty_PC,107,err_number) #A
        if(_):
            counter += 1
        window += bit # Covered
        PC += 1
        err_number,_ = fault_possibility(PC,faulty_PC,109,err_number) #A
        if(_):
            if(window == "1"):
                window = "0"
            elif(window == "0"):
                window = "1"
            else:
                window = window[:-1]
        if len(window) == width or counter == len(scalar_bits): # Covered
            window_value = int(window, 2) # Covered
            PC += 1
            err_number,_ = fault_possibility(PC,faulty_PC,112,err_number) #A/W
            if(_):
                window_value = window_value - 1
            for _ in range(len(window)): # Not Covered
                PC += 1
                err_number,_ = fault_possibility(PC,faulty_PC,114,err_number) #A
                if(_):
                    break
                result = result + result # Not Covered
                PC += 1
                err_number,_ = fault_possibility(PC,faulty_PC,116,err_number) #A
                if _:
                    result = result /2
            if(counter < len(scalar_bits)):
                try:
                    post_pattern_counter[window_value]+=1
                except Exception as e:
                    post_pattern_counter[window_value] = 1
            if window_value != 0:
                result = result + precomputed_points[window_value - 1]   #Not covered
                PC += 1
                err_number,_ = fault_possibility(PC,faulty_PC,123,err_number) #A/W
                # if(_):
                #     result = result + precomputed_points[window_value - 1]   #Not covered
            window = ""
    if(pre_pattern_counter != post_pattern_counter):
        detected_error += 1
    # print("Error numbers are {_} ".format(_=err_number))
    return err_number,result



sum = 0
my_len = 10000
zero_counter = 0
global detected_error
detected_error = 0
number_of_faults = 8
for i in range(my_len):
    err_number,_ = faulty_window_method(298121231233198792034237435695,198792034237435695423570985008687998753269985665640564012357584007913129639126+i,7,number_of_faults)
    if(err_number == 0):
        zero_counter += 1
    sum += err_number
print("Error numbers in average is {_} ".format(_=sum/my_len))
print("Zero error injection is {_} ".format(_=zero_counter))
print("Precision is: {precision}%, Number of samples: {my_len}, Detected errors by CC: {detected_error}"
      .format(my_len=my_len,
              detected_error=detected_error,
              precision=(detected_error/my_len)*100))
