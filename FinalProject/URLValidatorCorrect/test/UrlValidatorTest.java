/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** CONNIE MCCLUNG CS362 SPRING 2018
 *  EXTRA CREDIT ASSIGNMENT
 *  Write a random tester for URL Validator isValid() method
 *  My tester function is testRandomIsValid()
 */

import junit.framework.TestCase;
import java.util.Random; //added so that I can get random permutations for test cases

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1739358 $
 */
public class UrlValidatorTest extends TestCase {

   private final boolean printStatus = false;
   private final boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

  
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   @Override
protected void setUp() {
      for (int index = 0; index < testPartsIndex.length - 1; index++) {
         testPartsIndex[index] = 0;
      }
   }

   public void testIsValid() {
        testIsValid(testUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
        setUp();
//        int options =
//            UrlValidator.ALLOW_2_SLASHES
//                + UrlValidator.ALLOW_ALL_SCHEMES
//                + UrlValidator.NO_FRAGMENTS;
//    
//        testIsValid(testUrlPartsOptions, options);
   }
   //THIS IS PART OF MY CODE FOR EXTRA CREDIT
   public void testRandomIsValid() {
       testRandomIsValid(testUrlPartsRandom, UrlValidator.ALLOW_ALL_SCHEMES);//keeps same input parameters as testIsValid()
       setUp();
//       int options =
//           UrlValidator.ALLOW_2_SLASHES
//               + UrlValidator.ALLOW_ALL_SCHEMES
//               + UrlValidator.NO_FRAGMENTS;
//   

  }
   
   public void testIsValidScheme() {
      if (printStatus) {
         System.out.print("\n testIsValidScheme() ");
      }
      String[] schemes = {"http", "gopher"};
      //UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
      UrlValidator urlVal = new UrlValidator(schemes, 0);
      for (int sIndex = 0; sIndex < testScheme.length; sIndex++) {
         ResultPair testPair = testScheme[sIndex];
         boolean result = urlVal.isValidScheme(testPair.item);
         assertEquals(testPair.item, testPair.valid, result);
         if (printStatus) {
            if (result == testPair.valid) {
               System.out.print('.');
            } else {
               System.out.print('X');
            }
         }
      }
      if (printStatus) {
         System.out.println();
      }

   }

   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   public void testIsValid(Object[] testObjects, long allowAllSchemes) {
	      UrlValidator urlVal = new UrlValidator(null, null, allowAllSchemes);
	      //UrlValidator urlVal = new UrlValidator(null, allowAllSchemes);
      assertTrue(urlVal.isValid("http://www.google.com"));
      assertTrue(urlVal.isValid("http://www.google.com/"));
      int statusPerLine = 60;
      int printed = 0;
      if (printIndex)  {
         statusPerLine = 6;
      }
      do {
          StringBuilder testBuffer = new StringBuilder();
         boolean expected = true;
         for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
            int index = testPartsIndex[testPartsIndexIndex];
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);
            expected &= part[index].valid;
         }
         String url = testBuffer.toString();
         boolean result = urlVal.isValid(url);
         if(result == true)
        	 System.out.println(url);
         assertEquals(url, expected, result);
         if (printStatus) {
            if (printIndex) {
               System.out.print(testPartsIndextoString());
            } else {
               if (result == expected) {
                  System.out.print('.');
               } else {
                  System.out.print('X');
               }
            }
            printed++;
            if (printed == statusPerLine) {
               System.out.println();
               printed = 0;
            }
         }
      } while (incrementTestPartsIndex(testPartsIndex, testObjects));
      if (printStatus) {
         System.out.println();
      }
   }

   /**
    * 
    * HERE IS MY CODE FOR EXTRA CREDIT ASSIGNMENT
    * testRandomIsValid()
    * Random Tester for isValid()    
    * Create set of Random tests by taking the testUrlRandomXXX arrays and
    * generating random permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   public void testRandomIsValid(Object[] testObjects, long allowAllSchemes) {
	   boolean printStatus = true; //when enabled, will display test name, number of iterations, and invalid/valid statistics
	   boolean printVerbose = false; //set to true will print out each url with valid/invalid status as tested
	   
	   if (printStatus) {
	         System.out.print("\nRANDOM TESTER testIsValidRandom()\n");
	      }
	  UrlValidator urlVal = new UrlValidator(null, null, allowAllSchemes);
      assertTrue(urlVal.isValid("http://www.google.com"));
      //check for edge case of empty string for url
      assertTrue(!urlVal.isValid(null));
      
      
      //counter variables
      int counter = 0;
      int validcounter = 0;
      int invalidcounter = 0;
      //ADJUST VALUE OF N TO SET NUMBER OF ITERATIONSN
      int n = 10000;
      
   // create instance of Random class
      Random rand = new Random();
      
      //add a for loop
      for (int i = 0; i < n; i++) {
         StringBuilder testRandomBuffer = new StringBuilder();
         // About 1 in 100 times, randomly pass empty string instead of building a valid string
         int randUseEmpty = rand.nextInt((100) - 1 + 1) + 1;
         boolean expected = true;
         if (randUseEmpty==50) {
        	 testRandomBuffer.append("");
        	 expected = false;
         }
         else {
         int j = 0;
         int randSchemeIndex = rand.nextInt((testUrlSchemeRandom.length-2) - 0 + 1) + 0;
         ResultPair[] part =( ResultPair[]) testUrlPartsRandom[j];
         testRandomBuffer.append(part[randSchemeIndex].item);
         expected &= part[randSchemeIndex].valid;
         j++;
         
         int randUrlAuthorityIndex = rand.nextInt((testUrlAuthorityRandom.length-1) - 0 + 1) + 0;
         part =( ResultPair[]) testUrlPartsRandom[j];
         testRandomBuffer.append(part[randUrlAuthorityIndex].item);
         expected &= part[randUrlAuthorityIndex].valid;
         j++;
         
         int randUrlPortIndex = rand.nextInt((testUrlPortRandom.length-1) - 0 + 1) + 0;
         part =( ResultPair[]) testUrlPartsRandom[j];
         testRandomBuffer.append(part[randUrlPortIndex].item);
         expected &= part[randUrlPortIndex].valid;
         j++;
         
         int randTestPathIndex= rand.nextInt((testPathRandom.length-1) - 0 + 1) + 0;
         part =( ResultPair[]) testUrlPartsRandom[j];
         testRandomBuffer.append(part[randTestPathIndex].item);
         expected &= part[randTestPathIndex].valid;
         j++;
         
         int randTestUrlQueryIndex= rand.nextInt((testUrlQueryRandom.length-1) - 0 + 1) + 0;
         part =( ResultPair[]) testUrlPartsRandom[j];
         testRandomBuffer.append(part[randTestUrlQueryIndex].item);
         expected &= part[randTestUrlQueryIndex].valid;
         j++;
         }
         String url = testRandomBuffer.toString();


         boolean result = urlVal.isValid(url);
         counter++;
         if(result == true 
        		 )  {
        	if(printVerbose) {
        	System.out.println("Valid: "+ url);
        	}
        	validcounter++;
         }
         else {
         	if (printVerbose) {
        	 System.out.println("Invalid: "+ url);
         	}
        	 invalidcounter++;
         }
          assertEquals(url, expected, result);
   }
      if (printStatus) {
          System.out.println("Tests:" +counter);
          System.out.println("Valid:" + validcounter);
          System.out.println("Invalid:" + invalidcounter);
	      }

   }

   
   public void testValidator202() {
       String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
       urlValidator.isValid("http://www.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.log");
   }

   public void testValidator204() {
       String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
       assertTrue(urlValidator.isValid("http://tech.yahoo.com/rc/desktops/102;_ylt=Ao8yevQHlZ4On0O3ZJGXLEQFLZA5"));
   }

   static boolean incrementTestPartsIndex(int[] testPartsIndex, Object[] testParts) {
      boolean carry = true;  //add 1 to lowest order part.
      boolean maxIndex = true;
      for (int testPartsIndexIndex = testPartsIndex.length - 1; testPartsIndexIndex >= 0; --testPartsIndexIndex) {
         int index = testPartsIndex[testPartsIndexIndex];
         ResultPair[] part = (ResultPair[]) testParts[testPartsIndexIndex];
         if (carry) {
            if (index < part.length - 1) {
               index++;
               testPartsIndex[testPartsIndexIndex] = index;
               carry = false;
            } else {
               testPartsIndex[testPartsIndexIndex] = 0;
               carry = true;
            }
         }
         maxIndex &= (index == (part.length - 1));
      }


      return (!maxIndex);
   }

   private String testPartsIndextoString() {
       StringBuilder carryMsg = new StringBuilder("{");
      for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
         carryMsg.append(testPartsIndex[testPartsIndexIndex]);
         if (testPartsIndexIndex < testPartsIndex.length - 1) {
            carryMsg.append(',');
         } else {
            carryMsg.append('}');
         }
      }
      return carryMsg.toString();

   }

   public void testValidateUrl() {
      assertTrue(true);
   }

   /**
    * Only used to debug the unit tests.
    * @param argv
    */
   public static void main(String[] argv) {

	   UrlValidatorTest fct = new UrlValidatorTest("url test");
      fct.setUp();
      //fct.testIsValid();
      fct.testRandomIsValid();
      //fct.testIsValidScheme();
   }
   
   //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                              new ResultPair("h3t://", true),
                               new ResultPair("3ht://", false),
                               new ResultPair("http:/", false),
                              new ResultPair("http:", false),
                              new ResultPair("http/", false),
                              new ResultPair("://", false),
                              new ResultPair("", true)
                               };

   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
                                  new ResultPair("go.com", true),
                                 new ResultPair("go.au", true),
                                  new ResultPair("0.0.0.0", true),
                                 new ResultPair("255.255.255.255", true),
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("255.com", true),
                                  new ResultPair("1.2.3.4.5", false),
                                  new ResultPair("1.2.3.4.", false),
                                  new ResultPair("1.2.3", false),
                                  new ResultPair(".1.2.3.4", false),
                                  new ResultPair("go.a", false),
                                 new ResultPair("go.a1a", false),
                                  new ResultPair("go.1aa", false),
                                  new ResultPair("aaa.", false),
                                  new ResultPair(".aaa", false),
                                  new ResultPair("aaa", false),
                                  new ResultPair("", false)
   };
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
                             new ResultPair(":65535", true),
                             new ResultPair(":0", true),
                             new ResultPair("", true),
                             new ResultPair(":-1", false),
                            new ResultPair(":65636",false),
                             new ResultPair(":65a", false)
   };
   ResultPair[] testPath = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/test1/", true),
                          new ResultPair("", true),
                          new ResultPair("/test1/file", true),
                          new ResultPair("/..//file", false),
                          new ResultPair("/test1//file", false)
   };
   //Test allow2slash, noFragment
   ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                    new ResultPair("/t123", true),
                                    new ResultPair("/$23", true),
                                    new ResultPair("/..", false),
                                    new ResultPair("/../", false),
                                    new ResultPair("/test1/", true),
                                    new ResultPair("/#", false),
                                    new ResultPair("", true),
                                    new ResultPair("/test1/file", true),
                                    new ResultPair("/t123/file", true),
                                    new ResultPair("/$23/file", true),
                                    new ResultPair("/../file", false),
                                    new ResultPair("/..//file", false),
                                    new ResultPair("/test1//file", true),
                                    new ResultPair("/#/file", false)
   };

   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("", true)
   };

   //-------------------- Test data for creating a composite URL for Random Tester
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   //ALLOW ALL SCHEMES SWITCH ALLOWS ANY URL SCHEME THAT FITS REGEX EXPRESSION, ADDING MORE TRUE / FALSE EXAMPLES
   ResultPair[] testUrlSchemeRandom = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                               new ResultPair("h3t://", true),
                             //add more true cases because random construction is biased towards false
                              new ResultPair("gopher://", true),
								new ResultPair("test://",true),
                              new ResultPair("anothervalidhttps://",true),
                              new ResultPair("anothervalidftp://", true),
                             new ResultPair("anothervalidgopher://", true),
                             new ResultPair("https://",true),
                             new ResultPair("anothervalidhttps://",true),
                             //add some edge cases
                              new ResultPair("y://",true),
                              new ResultPair("testwithverylongstringthatismuchlongerthanusualurlschememuchmuchlongertoseeifaffectsresult://",true),
                              new ResultPair("TEST://", true),
                             new ResultPair("Y://", true),
                             new ResultPair("testWithCamelCase://",true),
                             new ResultPair("testWith123NumbersandCamelCase://",true),
                             new ResultPair("t1234://", true),
                             new ResultPair("t12T34T://", true),
                             new ResultPair("TESTWITHLONGSTRINGVERYLONGSTRINGEXTRALONGSTRINGINALLCAPSTOSEEIFAFFECTSRESULTSUSINGCAPSINSTEADOFLOWERCASE://",true),
                              //false cases
                             
                             new ResultPair("ftp:/", false),
                             new ResultPair("3ht://", false),
                             new ResultPair("http:/", false),
                              new ResultPair("http:", false),
                              new ResultPair("http/", false),
                              new ResultPair("://", false),
                              //add some  edge cases

                              new ResultPair("TEST:/", false),
                             new ResultPair("tESt:/", false),
                             new ResultPair("testingverylongstringwithsingleslashtoseeifanyaffectonresult:/", false),
                             new ResultPair("T:/", false),
                             new ResultPair("t:/", false),
                             new ResultPair("TESTINGVERYLONGSTRINGFORURLMUCHLONGERTHANUSUALISITTOOLONGKEEPEXTENDINGLENGTISTHEREALIMITTOHOWLONGITCANBEKEEPEXTENDINGLENGTH:/", false),
                             new ResultPair("t@1234?t://", false),
                             new ResultPair("1234://", false),
                             new ResultPair("3Ht://", false),
                             
                             new ResultPair("HTTP:", false),
                             new ResultPair("H:", false),
                             new ResultPair("h:/", false),
                             new ResultPair("HTTPveryLongCamelCaseStringWithVarious3Numbers4AndLettersTHEEND:", false),
                             new ResultPair("HTTP1234MixUpperandLowerCase:", false),
                             
                             new ResultPair("HTTP/", false),
                             new ResultPair("H/", false),
                             new ResultPair("h/", false),
                             new ResultPair("HTTPveryLongCamelCaseStringWithVarious3Numbers4AndLettersTHEEND/", false),
                             new ResultPair("HTTP1234MixUpperandLowerCase/", false), 
                             new ResultPair("HTTP/", false)
                              

                              //new ResultPair("", true)
                               };

   ResultPair[] testUrlAuthorityRandom = {new ResultPair("www.google.com", true),
                                  new ResultPair("go.com", true),
                                 new ResultPair("go.au", true),
                                  new ResultPair("0.0.0.0", true),
                                  new ResultPair("255.com", true),
                                 new ResultPair("255.255.255.255", true),
                                 
                                 //add some true edge cases
                                 new ResultPair("www.g.com", true),
                                 new ResultPair("www.verylongveryverylongveryverlongveryverylongveryverylongname.com", true),
                                 new ResultPair("WWW.ALLCAPS.COM", true),
                                 new ResultPair("www.VerylongwithCaseANDOTHERvariationsinNameIsValidStill.com", true),
                                 new ResultPair("1111111111111111111111111111111111111111111111111111111111111.com", true),
                                 new ResultPair("GO.FR", true),
                                 new ResultPair("0.255.0.255", true),
                                 new ResultPair("H.com", true),	
                                 new ResultPair("www.12345.com", true),	
                                 new ResultPair("g.fr", true),
                                 new ResultPair("test.com.", true),
                                 
                                 
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("1.2.3.4.5", false),
                                  new ResultPair("1.2.3.4.", false),
                                  new ResultPair("1.2.3", false),
                                  new ResultPair(".1.2.3.4", false),
                                  new ResultPair("go.a", false),
                                 new ResultPair("go.a1a", false),
                                  new ResultPair("go.1aa", false),
                                  new ResultPair("aaa.", false),
                                  new ResultPair(".aaa", false),
                                  new ResultPair("aaa", false),
                                  new ResultPair("", false),
                                  
                                  //add some false edge cases
                                  new ResultPair("256.256.256.256.256", false),
                                  new ResultPair("111111111111111111111111111111111111111111111111111111111111111111111111111111111.com", false),
                                  new ResultPair("www.0.c", false),
                                  new ResultPair("www.google.extremelylonginvalidstringthatdoesntmatchanything", false),
                                  new ResultPair("www.test.com.fr.a", false),
                                  new ResultPair("0", false)
                                  
                                  
                                  
   };
   ResultPair[] testUrlPortRandom = {new ResultPair(":80", true),
                             new ResultPair(":65535", true),
                             new ResultPair(":0", true),
                             new ResultPair("", true),
                             //add some true edge cases
                             new ResultPair(":00000000000000000000000000000000000000000000000000000", true),
                             new ResultPair(":00000000000000000000000000000000000000000000000000080", true),
                             
                             new ResultPair(":-1", false),
                            new ResultPair(":65636",false),
                             new ResultPair(":65a", false),
                             //add some false edge cases
                             new ResultPair(":999999999999999999999999999999999999999999999999", false),
                            new ResultPair("65636",false),
                             new ResultPair(":65a!", false),
                             new ResultPair(":65a!65", false),
                             new ResultPair("80",false),
                             new ResultPair("0",false),
                             new ResultPair("test", false),
                             new ResultPair(":-0", false),
                            new ResultPair(":-65636",false),
                             new ResultPair(":65a12345", false),
   };
   ResultPair[] testPathRandom = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/test1/", true),
                          new ResultPair("", true),
                          new ResultPair("/test1/file", true),
                          
                          //add some true edge cases
                          new ResultPair("/t", true),
                          new ResultPair("/verylongpathhowlongistoolongIdontknowforsurecheckingbyusingthislongfilename", true),
                          new ResultPair("/123456789999999999999999999999999999999999999999999999999999999999999999999", true),
                          new ResultPair("/$@!@#$%#@!@$$@$@@@@@@@@%******$$$#@@@@##@##$$$$$$$@@#", true),
                          new ResultPair("/@", true),
                          new ResultPair("/testinganotherveryLONGfolderNameWith_Characters123Numbers_ETC_ISitValidWhoKnows/", true),
                          new ResultPair("/test1folderiwithlongcomplex12345FileName_andSpecialCharaters@@@/filenameisALsoLONGand2134Complicated1313138383838383838383883", true),
                          //these are also true based on the way isValidPath() evaluates
                          new ResultPair("/.", true),
                          new ResultPair("/./", true),
                          new ResultPair("/.wordsinthemiddle./", true),
                          
                          
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/..//file", false),
                          new ResultPair("/test1//file", false),
                          
                          //add some false edge cases
                          new ResultPair("/.    .", false),
                          new ResultPair("/.   ./", false),
                          new ResultPair("/.  .//file", false),
                          new ResultPair("/test    1//file", false),
                          new ResultPair("/test    1//fi    le", false),
   };
   //Test allow2slash, noFragment //NOT ADDRESSED IN RANDOM TESTER 1.0
   ResultPair[] testUrlPathOptionsRandom = {new ResultPair("/test1", true),
                                    new ResultPair("/t123", true),
                                    new ResultPair("/$23", true),
                                    new ResultPair("/..", false),
                                    new ResultPair("/../", false),
                                    new ResultPair("/test1/", true),
                                    new ResultPair("/#", false),
                                    new ResultPair("", true),
                                    new ResultPair("/test1/file", true),
                                    new ResultPair("/t123/file", true),
                                    new ResultPair("/$23/file", true),
                                    new ResultPair("/../file", false),
                                    new ResultPair("/..//file", false),
                                    new ResultPair("/test1//file", true),
                                    new ResultPair("/#/file", false)
   };

   ResultPair[] testUrlQueryRandom = {new ResultPair("?action=view", true),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("", true)
   };

   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   
   Object[] testUrlPartsRandom = {testUrlSchemeRandom, testUrlAuthorityRandom, testUrlPortRandom, testPathRandom, testUrlQueryRandom};
  
   Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
   int[] testPartsIndex = {0, 0, 0, 0, 0};

   //---------------- Test data for individual url parts ----------------
   ResultPair[] testScheme = {new ResultPair("http", true),
                            new ResultPair("ftp", false),
                            new ResultPair("httpd", false),
                            new ResultPair("telnet", false)};


}