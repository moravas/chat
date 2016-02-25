using System;
using Microsoft.Owin.Hosting;

namespace Server
{
    class Program
    {
        static void Main(string[] args)
        {
            string baseUri = "http://localhost:8080";
            Console.WriteLine("Starting web Server...");
            using (WebApp.Start<WebApiConfig>(baseUri))
            {
                Console.WriteLine("Server running at {0} - press Enter to quit. ", baseUri);
                Console.ReadLine();
            }
        }
    }
}
