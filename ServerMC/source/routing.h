#include <crow.h>

namespace http
{
	struct Player {
		int x, y;
	};

	class Routing
	{
	public:
		void Run(Player& player);

	private:
		//crow::response AddProductToBasketRoute(ProductStorage& storage, const crow::request& req, int productId )const;

	private:
		crow::SimpleApp m_app;
	};
}