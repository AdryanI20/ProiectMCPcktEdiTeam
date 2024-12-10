#include "routing.h"
import utils;
using namespace http;

void Routing::Run(Player& player)
{
	CROW_ROUTE(m_app, "/")([&player]() {
		return std::to_string(player.x)+" "+std::to_string(player.y);
		});

	CROW_ROUTE(m_app, "/get_player_position")
		([&player]() {
		crow::json::wvalue response;
		response["x"] = player.x;
		response["y"] = player.y;
		return response;
			});

	CROW_ROUTE(m_app, "/move_player")
		.methods(crow::HTTPMethod::PUT)
		([&player](const crow::request& req) 
		{
			auto bodyArgs = parseUrlArgs(req.body);
			auto end = bodyArgs.end();
			auto XIter = bodyArgs.find("dx");
			auto YIter = bodyArgs.find("dy");
			int dx = player.x;
			int dy = player.y;
			if (XIter != end && YIter != end)
			{
				dx = std::stoi(XIter->second);
				dy = std::stoi(YIter->second);
			}
			player.x = dx;
			player.y = dy;
			return crow::response(204);
			//char* dx_chr = req.url_params.get("dx");
			//char* dy_chr = req.url_params.get("dy");
			//int dx = player.x;
			//int dy = player.y;
			//if (dx_chr != nullptr)
			//	dx = std::stoi(dx_chr);
			//if (dy_chr != nullptr)
			//	dy = std::stoi(dy_chr);
			//player.x = dx;
			//player.y = dy;
			//return crow::response(200);
		});

	//CROW_ROUTE(m_app, "/products")([&storage]() {
	//	std::vector<crow::json::wvalue> products_json;

	//	auto products = storage.GetProducts();
	//	for (const auto& product : products)
	//	{
	//		products_json.push_back(crow::json::wvalue{
	//			{"id", product.GetId()},  // product_json["id"] = product.id;
	//			{"name", product.GetName()},
	//			{"price", product.GetPrice()}
	//			});

	//		//std::string product_json = db.dump(product);	
	//	}
	//	return crow::json::wvalue{ products_json };
	//	});


	//CROW_ROUTE(m_app, "/addproducttobasket/<int>")([&storage, this](const crow::request& req, int productId) {
	//	return AddProductToBasketRoute(storage, req, productId);
	//	
	//	});

	//auto& addToBasketPut = CROW_ROUTE(m_app, "/addproducttobasket")
	//	.methods(crow::HTTPMethod::PUT); // https://stackoverflow.com/a/630475/12388382
	//addToBasketPut(AddToBasketHandler(storage));


	//CROW_ROUTE(m_app, "/basket")([&storage]() {
	//	auto rows = storage.GetBasket();

	//	std::vector<crow::json::wvalue> results;
	//	for (const auto& row : rows) {
	//		const auto& [name, price, quantity] = row;
	//		results.push_back(crow::json::wvalue{
	//			{ "name", name },
	//			{ "price", price },
	//			{ "quantity", quantity }
	//			});
	//	}

	//	return crow::json::wvalue{ results };
	//	});

	m_app.port(18080).multithreaded().run();

}

//crow::response Routing::AddProductToBasketRoute(ProductStorage& storage, const crow::request& req, int productId) const
//{
//	// validate productId
//	char* quantity_chr = req.url_params.get("quantity");
//	int quantity = 1;
//	if (quantity_chr != nullptr) {
//		quantity = std::stoi(quantity_chr); // on failure?
//	}
//
//	storage.AddProductToShoppingBasket(productId, quantity);
//
//	return crow::response(200);;
//}
