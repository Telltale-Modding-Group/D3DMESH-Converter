using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace converter
{
    public static class _3DSMaxFunctions
    {
        /// <summary>
        /// Gets the bytes of a file.
        /// <para>https://help.autodesk.com/view/3DSMAX/2016/ENU/?guid=__files_GUID_423269A5_B395_4A90_8058_F96C0A24115F_htm</para>
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public static byte[] fopen(string filePath)
        {
            return File.ReadAllBytes(filePath);
        }

        /*
        fn ReadFixedString bstream fixedLen = (
		    local str = ""

		    for i = 1 to fixedLen do
		    (
			    str += bit.intAsChar (ReadByte bstream #unsigned)
		    )
		    str
        )
        */

        /*
        fn floatSwap2 f = (
		    i = bit.floatAsInt f
		    h = bit.intashex i
		    while h.count < 8 do h = "0" + h
		        s = (substring h 7 2) + (substring h 5 2) + (substring h 3 2) + (substring h 1 2)
		        bit.intAsFloat (bit.hexasint s)
	    )
        */

        /*
        fn convertTo32 input16 = (
		    inputAsInt = input16
		    sign = bit.get inputAsInt 16
		    exponent = (bit.shift (bit.and inputAsInt (bit.hexasint "7C00")) -10) as integer - 16
		    fraction = bit.and inputAsInt (bit.hexasint "03FF")
		    if sign==true then sign = 1 else sign = 0
		    exponentF = exponent + 127
		    outputAsFloat = bit.or (bit.or (bit.shift fraction 13) (bit.shift exponentF 23)) (bit.shift sign 31)
		    return bit.intasfloat outputasfloat
	    )
        */

        /*
        fn readHalfFloat fstream = (
		    return convertTo32(Readshort fstream)
	    )
        */

        /*
        fn ReadBEShort fstream = (bit.swapBytes (readshort fstream #unsigned) 1 2)
        */

        /*
        fn ReadBELong fstream = (bit.swapBytes (bit.swapBytes (readlong f #unsignedstream #unsigned) 1 4) 2 3)
        */

        /*
        fn ReadBEFloat fstream = (bit.intAsFloat (bit.swapBytes (bit.swapBytes (readlong f #unsignedstream #unsigned) 1 4) 2 3))
        */

        /*
        fn ReadBEHalfFloat fstream = (return convertTo32(ReadBEshort fstream))
        */

        /*
        
        */
    }
}
