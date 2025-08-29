package main

import "fmt"

func main() {
	ExampleUsingDynamicFpe()
	//ExampleUsingStaticFpe()
}

func ExampleUsingStaticFpe() {
	voltageURL := "https://voltage-pp-0000.opentext.co.id/policy/clientPolicy.xml"
	trustPath := "/opt/simple-api/trustStore-cloud"
	cachePath := "/opt/simple-api/cache"
	identity := "developer@ori.co.id"
	sharedSecret := "voltage123"
	format := "alphanumeric"

	fpe := NewVoltageFPE(
		voltageURL,
		trustPath,
		cachePath,
		identity,
		sharedSecret,
		format,
	)
	defer fpe.Close()

	plaintext := "12-10-2005 10:27:33"
	cipher := fpe.Protect(plaintext)
	recovered := fpe.Access(cipher)

	fmt.Println("Original: ", plaintext)
	fmt.Println("Cipher:   ", cipher)
	fmt.Println("Recovered:", recovered)
}

func ExampleUsingDynamicFpe() {
	voltageURL := "https://voltage-pp-0000.opentext.co.id/policy/clientPolicy.xml"
	trustPath := "/opt/simple-api/trustStore-cloud"
	cachePath := "/opt/simple-api/cache"
	RegisterFPE("fpe-dev", voltageURL, trustPath, cachePath, "developer@ori.co.id", "voltage123", "alphanumeric")

	cipher, _ := EncryptByID("fpe-dev", "12-10-2005 10:27:33")
	plain, _ := DecryptByID("fpe-dev", cipher)

	DeleteAllFPEs() // --> optional

	fmt.Println("Original: ", plain)
	fmt.Println("Cipher:   ", cipher)
}
