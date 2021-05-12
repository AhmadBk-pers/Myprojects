#!/usr/bin/env python
#-*- coding: utf-8 -*-

'''
Usage Example -
python steganography.py -f X.bmp -o Y.bmp -m "Hidden message!"
'''



from optparse import OptionParser


__author__ = "ITC"
__license__ = "GPLv3"

from PIL import Image

try:
   input = raw_input
except NameError:
   pass


def set_bit(v, index, x):
  """Set the index:th bit of v to 1 if x is truthy, else to 0, and return the new value."""
  mask = 1 << index
  v &= ~mask
  if x:
    v |= mask
  return v

def setlsb(component, bit):
    """
    Set Least Significant Bit of a colour component.
    """
    return component & ~1 | int(bit)

def a2bits_list(chars):
    """
    Convert a string to its bits representation as a list of 0's and 1's.
    """
    return [bin(ord(x))[2:].rjust(8,"0") for x in chars]

def fib():
    a, b = 0, 1
    while 1:
        yield a
        a, b = b, a + b

def hide(input_image_file, message, auto_convert_rgb=False, order_func = fib):
    """
    Hide a message (string) in an image with a  (Least Significant Bit) technique.
    """


    message_length = len(message)
    assert message_length != 0, "message length is zero"

    img = Image.open(input_image_file)
	
    if img.mode not in ['RGB', 'RGBA']:
        if not auto_convert_rgb:
            print('The mode of the image is not RGB. Mode is {}'.\
                                                            format(img.mode))
            answer = input('Convert the image to RGB ? [Y / n]\n') or 'Y'
            if answer.lower() == 'n':
                raise Exception('Not a RGB image.')
        img = img.convert('RGB')

    hidden_bits_order = order_func()
    encoded = img.copy()
    width, height = img.size
    index = 0

    message = str(message_length) + ":" + str(message)
    message_bits = "".join(a2bits_list(message))
    message_bits += '0' * ((3 - (len(message_bits) % 3)) % 3)
    
    npixels = width * height
    len_message_bits = len(message_bits)
    if len_message_bits > npixels * 3:
        raise Exception("The message you want to hide is too long: {}". \
                                                        format(message_length))
    for row in range(height):
        for col in range(width):
            if index + 3 <= len_message_bits :

                # Get the colour component.
                pixel = img.getpixel((col, row))
                r = pixel[0]
                g = pixel[1]
                b = pixel[2]

                # Change the Least Significant Bit of each colour component.
                # Get next bit to hide.
                bit = hidden_bits_order.next() % 8
                r = set_bit(r, bit, ('1' == message_bits[index]))
                g = set_bit(g, bit, ('1' == message_bits[index+1]))
                b = set_bit(b, bit, ('1' == message_bits[index+2]))

                # Save the new pixel
                if img.mode == 'RGBA':
                    updated_pixel = (r, g, b, pixel[3])
                else:
                    updated_pixel = (r, g, b)

                encoded.putpixel((col, row), updated_pixel)

                index += 3
            else:
                img.close()
                return encoded

    img.close()
    return encoded


def write(image, output_image_file):
    """
    Writes the output image file to disk, handles exceptions.
    """
    try:
        image.save(output_image_file)
    except Exception as e:
        # If hide() returns an error (Too long message).
        print(e)
    finally:
        image.close()

def main():

    # Read the imahe from disk
    encoded = hide(options.input_file, options.message, True)
    write(encoded, options.output_file)


if __name__ == "__main__" :
    parser = OptionParser()
    parser.add_option("-f", "--input-file", dest="input_file",
                      help="input image file", action="store", type="string")

    parser.add_option("-o", "--output-file", dest="output_file",
                      help="output image file", action="store", type="string")

    parser.add_option("-m", "--message", dest="message",
                      help="message to encode", action="store", type="string")

    (options, args) = parser.parse_args()

    if None in (options.input_file, options.output_file, options.message):  # if filename is not given
        parser.error('Aall parameters are required')

    main()






