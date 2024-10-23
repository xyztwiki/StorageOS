Imports Microsoft.AspNetCore.Builder
Imports Microsoft.AspNetCore.Hosting
Imports Microsoft.AspNetCore.Http
Imports Microsoft.Extensions.DependencyInjection
Imports Microsoft.Extensions.Hosting

Module Program
    Sub Main(args As String())
        CreateHostBuilder(args).Build().Run()
    End Sub

    Public Function CreateHostBuilder(args As String()) As IHostBuilder
        Return Host.CreateDefaultBuilder(args) _
            .ConfigureWebHostDefaults(Sub(webBuilder)
                                          webBuilder.UseStartup(Of Startup)()
                                      End Sub)
    End Function
End Module

Public Class Startup
    Public Sub ConfigureServices(services As IServiceCollection)
        ' Add services to the container if needed
    End Sub

    Public Sub Configure(app As IApplicationBuilder, env As IWebHostEnvironment)
        If env.IsDevelopment() Then
            app.UseDeveloperExceptionPage()
        End If

        app.UseRouting()

        app.UseEndpoints(Sub(endpoints)
                             endpoints.MapGet("/", Async Function(context) 
                                 Await context.Response.WriteAsync("Hello from ASP.NET Core Web API!")
                             End Function)

                             endpoints.MapGet("/api/greet/{name}", Async Function(context) 
                                 Dim name = context.Request.RouteValues("name").ToString()
                                 Await context.Response.WriteAsync($"Hello, {name}!")
                             End Function)

                             endpoints.MapGet("/api/time", Async Function(context) 
                                 Await context.Response.WriteAsync($"Current time is: {DateTime.Now}")
                             End Function)
                         End Sub)
    End Sub
End Class