import multiprocessing
from communication import communicate_uart_data
from plot_data import plot_data, test_serial

def main():
    print("Starting...")
    # Create a queue for inter-process communication
    data_queue = multiprocessing.Queue()
    command_queue = multiprocessing.Queue()
    # Create an Event for signaling the processes to exit
    exit_event = multiprocessing.Event()

    # Create the first process
    p_uart = multiprocessing.Process(target=communicate_uart_data, args=(data_queue, command_queue, exit_event))
    p_uart.start()

    # Create the second process
    p_dataprocessing = multiprocessing.Process(target=test_serial, args=(data_queue, exit_event))
    p_dataprocessing.start()

    try:
        # Wait for both processes to finish
        p_uart.join()
        p_dataprocessing.join()
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        exit_event.set()
        p_uart.join()
        p_dataprocessing.join()
        if p_dataprocessing.is_alive() & p_uart.is_alive():
            print("Warning: process did not terminate correctly")
        else:
            print("Process terminated correctly")
   

if __name__ == "__main__":
    main()