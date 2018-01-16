#include <iostream>
#include <chrono>

#include <../OpenGL Graphics/OpenGL Graphics.hpp>
namespace GVE = GreatVEngine2;
using namespace GVE;

void test1()
{
	auto openGLEngine = Make<Graphics::APIs::OpenGL::Engine>();
	{
		auto scene = Make<Graphics::Scene>(openGLEngine);
		auto material = Make<Graphics::Material>(openGLEngine);
		auto model = Make<Graphics::Model>(openGLEngine);

		auto object1 = Make<Graphics::Object>(material, model, openGLEngine);

		scene->Add(object1);
		scene->Remove(object1);

		scene->Add(object1);
		scene->Remove(object1);

		auto object2 = Make<Graphics::Object>(material, model, openGLEngine);

		scene->Add(object1);
		scene->Add(object2);
		scene->Remove(object1);
		scene->Remove(object2);

		scene->Add(object1);
		scene->Add(object2);
		scene->Remove(object2);
		scene->Remove(object1);
	}
	{
		auto scene = Make<Graphics::Scene>(openGLEngine);
		auto material = Make<Graphics::Material>(openGLEngine);
		auto model = Make<Graphics::Model>(openGLEngine);

		auto object1 = Make<Graphics::Object>(material, model, openGLEngine);

		scene->Add(object1);
		scene->Remove(object1);
	}
}
void test2()
{
	using T = std::chrono::microseconds;
	T t = T::zero();
	Size m = 50;

	for (Size i = 0; i < m; ++i)
	{
		auto openGLEngine = Make<Graphics::APIs::OpenGL::Engine>();

		auto scene = Make<Graphics::Scene>(openGLEngine);
		Vector<StrongPointer<Graphics::Material>> materials(10);
		{
			for (auto &material : materials)
			{
				material = Make<Graphics::Material>(openGLEngine);
			}
		}
		Vector<StrongPointer<Graphics::Model>> models(10);
		{
			for (auto &model : models)
			{
				model = Make<Graphics::Model>(openGLEngine);
			}
		}
	
		// std::cout << "begin" << std::endl;

		Vector<StrongPointer<Graphics::Object>> objects(1000);
		{
			auto start = std::chrono::high_resolution_clock::now();
			
			for (auto &object : objects)
			{
				auto &material	= materials[rand() % materials.size()];
				auto &model		= models[rand() % models.size()];
				
				object = Make<Graphics::Object>(material, model, openGLEngine);

				scene->Add(object);
			}
		
			// std::cout << "middle" << std::endl;

			for (auto &object : objects)
			{
				scene->Remove(object);
			}
			
			auto finish = std::chrono::high_resolution_clock::now();
			
			auto time = std::chrono::duration_cast<T>(finish - start);
			t += time;

			std::cout << "time: " << time.count() << std::endl;
		}

		// std::cout << "end" << std::endl;
	}

	t /= m;

	std::cout << "average: " << t.count() << std::endl;
}

void main()
{
	auto engine = Make<Graphics::APIs::OpenGL::Engine>();

	auto material = Make<Graphics::Material>(engine);
	auto model = Make<Graphics::Model>(engine);

	auto object = Make<Graphics::Object>(material, model, engine);

	auto scene = Make<Graphics::Scene>(engine);

	scene->Add(object);

	auto view = Make<Graphics::View>();
	auto camera = Make<Graphics::Camera>();

	scene->Render(view, camera);

	scene->Remove(object);

	std::system("pause");
}