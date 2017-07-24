#include <Hexacrypt.h>

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension hexacrypt("Hexacrypt", "1.0");
        
        //Include the functions
		hexacrypt.add<Hexacrypt_Encrypt>("Hexacrypt_Encrypt", {
			Php::ByVal("plaintext", Php::Type::String),
			Php::ByVal("key", Php::Type::String)
		});

        hexacrypt.add<Hexacrypt_Decrypt>("Hexacrypt_Decrypt", {
			Php::ByVal("ciphertext", Php::Type::String),
			Php::ByVal("key", Php::Type::String)
		});


        // return the extension
        return hexacrypt;
    }
}
