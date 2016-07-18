#r "System.Net.Http"

using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.Net.Http;
using System.Threading.Tasks;

const string SERVER = "https://us.wio.seeed.io/v1";

// ASK FOR TOKEN
string _token;
if (Env.ScriptArgs.Count == 0)
{
    Console.WriteLine("Please enter your device token.");
    Console.Write('>');
    _token = Console.ReadLine();
}
else
{
    _token = Env.ScriptArgs[0];
}

Deploy(_token).Wait();

/// <summary>
/// Deploy an update to the iot servers.
/// </summary>
public async Task Deploy(string token)
{
    // 1. READ SOURCE FILES
    string cpp = EscapeJson(File.ReadAllText("Main.cpp"));
    string h = EscapeJson(File.ReadAllText("Main.h"));

    // 2. MAKE JSON FILE
    string json = String.Format(@"{{""./Main.h"":""{0}"",""./Main.cpp"":""{1}""}}", h, cpp);

    // 3. STARTUP HTTP CLIENT
    HttpClient client = new HttpClient();
    client.DefaultRequestHeaders.Add("Authorization", $"token {token}");

    // 4. PUSH TO SERVER
    Console.ForegroundColor = ConsoleColor.Blue;
    Console.WriteLine("Pushing to server...");

    HttpResponseMessage deploy =
        await client.PostAsync($"{SERVER}/cotf/project", new StringContent(json, Encoding.UTF8, "application/json"));

    if (!deploy.IsSuccessStatusCode)
    {
        client.Dispose();
        Console.WriteLine("Error while pushing to server: {0}", await deploy.Content.ReadAsStringAsync() ?? deploy.ReasonPhrase);
        Environment.Exit((int)deploy.StatusCode);
    }

    // 5. START BUILD PROCESS
    Console.ForegroundColor = ConsoleColor.Red;
    Console.WriteLine("Starting build...");

    HttpResponseMessage build =
        await client.PostAsync($"{SERVER}/ota/trigger", new StringContent(EscapeJson(CONNECTION_CONFIG), Encoding.UTF8, "application/json"));

    if (!build.IsSuccessStatusCode)
    {
        client.Dispose();
        Console.WriteLine("Error while triggering build: {0}", await build.Content.ReadAsStringAsync() ?? build.ReasonPhrase);
        Environment.Exit((int)build.StatusCode);
    }

    // 6. LOG OUTPUT
    Console.ForegroundColor = ConsoleColor.White;
    Console.WriteLine("Build has been started. You can check its state using the following command:");
    Console.WriteLine($"curl {SERVER}/ota/status?access_token={token}");
    client.Dispose();
}

public const string CONNECTION_CONFIG = @"{
    ""board_name"": ""Wio Link v1.0"",
    ""connections"": [
        { ""sku"": ""101020003"", ""port"": ""D0"" },
        { ""sku"": ""104990089"", ""port"": ""D2"" },
        { ""sku"": ""101020083"", ""port"": ""I2C0"" }
    ]
}";

public string EscapeJson(string json)
{
    return json.Replace("\r", String.Empty).Replace("\"", "\\\"").Replace("\n", "\\n");
}