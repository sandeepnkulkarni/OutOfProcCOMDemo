using System;
using System.Runtime.InteropServices;

namespace ManagedClient
{
    internal sealed class Constants
    {
        public const string MathServerClass = "4066a17c-c559-4a45-a02f-ae222bc3e50e";
        public static readonly Guid MathServerClassGuid = Guid.Parse(MathServerClass);

        public const string MathServerInterface = "fc41df7f-f647-40e9-bd9e-98476a9cb3ec";

        public const string TypeLibraryName = "Server.Contract.tlb";
    }

    [ComVisible(true)]
    [Guid(Constants.MathServerInterface)]
    public interface IMathServer
    {
        /// <summary>
        /// Compute the value of the constant Pi.
        /// </summary>
        double ComputePi();
    }

    class Program
    {
        static void Main(string[] args)
        {
            // If the COM server is registered as an in-proc server (as is the case when using
            // a DLL surrogate), activation through the Activator will only use the out-of-proc
            // server if the client and the registered COM server are not the same bitness.
            //
            // Type t = Type.GetTypeFromCLSID(Contract.Constants.ServerClassGuid);
            // var server = (IServer)Activator.CreateInstance(t);
            //
            // This demo explicitly calls CoCreateInstance with CLSCTX_LOCAL_SERVER to force
            // usage of the out-of-proc server.
            object obj;
            int hr = Ole32.CoCreateInstance(Constants.MathServerClassGuid, IntPtr.Zero, Ole32.CLSCTX_LOCAL_SERVER, typeof(IMathServer).GUID, out obj);
            if (hr < 0)
            {
                Marshal.ThrowExceptionForHR(hr);
            }

            var server = (IMathServer)obj;
            double pi = server.ComputePi();
            Console.WriteLine($"\u03C0 = {pi}");
        }

        private class Ole32
        {
            // https://docs.microsoft.com/windows/win32/api/wtypesbase/ne-wtypesbase-clsctx
            public const int CLSCTX_LOCAL_SERVER = 0x4;

            // https://docs.microsoft.com/windows/win32/api/combaseapi/nf-combaseapi-cocreateinstance
            [DllImport(nameof(Ole32))]
            public static extern int CoCreateInstance(
                [In, MarshalAs(UnmanagedType.LPStruct)] Guid rclsid,
                IntPtr pUnkOuter,
                uint dwClsContext,
                [In, MarshalAs(UnmanagedType.LPStruct)] Guid riid,
                [MarshalAs(UnmanagedType.IUnknown)] out object ppv);
        }
    }
    
}
